#include "Geometry3D.h"
#include <cmath>
#include <cfloat>
#include <list>

#define CMP(x, y) \
	(fabsf(x - y) <= FLT_EPSILON * fmaxf(1.0f, fmaxf(fabsf(x), fabsf(y))))

float Length(const Line& line) {
	return Magnitude(line.start - line.end);
}

float LengthSq(const Line& line) {
	return MagnitudeSq(line.start - line.end);
}

physRay FromPoints(const Point& from, const Point& to) {
	return physRay(
		from,
		Normalized(to - from)
	);
}

physvec3 GetMin(const physAABB& aabb) {
	physvec3 p1 = aabb.position + aabb.size;
	physvec3 p2 = aabb.position - aabb.size;

	return physvec3(fminf(p1.x, p2.x), fminf(p1.y, p2.y), fminf(p1.z, p2.z));
}
physvec3 GetMax(const physAABB& aabb) {
	physvec3 p1 = aabb.position + aabb.size;
	physvec3 p2 = aabb.position - aabb.size;

	return physvec3(fmaxf(p1.x, p2.x), fmaxf(p1.y, p2.y), fmaxf(p1.z, p2.z));
}

physAABB FromMinMax(const physvec3& min, const physvec3& max) {
	return physAABB((min + max) * 0.5f, (max - min) * 0.5f);
}

float PlaneEquation(const Point& point, const Plane& plane) {
	return Dot(point, plane.normal) - plane.distance;
}

float PlaneEquation(const Plane& plane, const Point& point) {
	return Dot(point, plane.normal) - plane.distance;
}

std::ostream& operator<<(std::ostream& os, const Line& shape) {
	os << "start: (" << shape.start.x << ", " << shape.start.y << ", " << shape.start.z << "), end: (";
	os << shape.end.x << ", " << shape.end.y << ", " << shape.end.z << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, const physRay& shape) {
	os << "origin: (" << shape.origin.x << ", " << shape.origin.y << ", " << shape.origin.z << "), ";
	os << "direction: (" << shape.direction.x << ", " << shape.direction.y << ", " << shape.direction.z << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, const Sphere& shape) {
	os << "position:" << shape.position.x << ", " << shape.position.y << ", " << shape.position.z << "), ";
	os << "radius: " << shape.radius;
	return os;
}

std::ostream& operator<<(std::ostream& os, const physAABB& shape) {
	physvec3 min = GetMin(shape);
	physvec3 max = GetMax(shape);
	os << "min: (" << min.x << ", " << min.y << ", " << min.z << "), ";
	os << "max: (" << max.x << ", " << max.y << ", " << max.z << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, const Plane& shape) {
	os << "normal: (" << shape.normal.x << ", " << shape.normal.y << ", " << shape.normal.z << "), ";
	os << "distance: " << shape.distance;
	return os;
}

std::ostream& operator<<(std::ostream& os, const Triangle& shape) {
	os << "a: (" << shape.a.x << ", " << shape.a.y << ", " << shape.a.z << "), ";
	os << "b: (" << shape.b.x << ", " << shape.b.y << ", " << shape.b.z << "), ";
	os << "c: (" << shape.c.x << ", " << shape.c.y << ", " << shape.c.z << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, const OBB& shape) {
	os << "position:" << shape.position.x << ", " << shape.position.y << ", " << shape.position.z << "), ";
	os << "size:" << shape.size.x << ", " << shape.size.y << ", " << shape.size.z << "), ";
	os << "x basis:" << shape.orientation._11 << ", " << shape.orientation._21 << ", " << shape.orientation._31 << "), ";
	os << "y basis:" << shape.orientation._12 << ", " << shape.orientation._22 << ", " << shape.orientation._32 << "), ";
	os << "z basis:" << shape.orientation._13 << ", " << shape.orientation._23 << ", " << shape.orientation._33 << ")";
	return os;
}

bool PointInSphere(const Point& point, const Sphere& sphere) {
	return MagnitudeSq(point - sphere.position) < sphere.radius * sphere.radius;
}

bool PointOnPlane(const Point& point, const Plane& plane) {
	// This should probably use an epsilon!
	//return Dot(point, plane.normal) - plane.distance == 0.0f;

	return CMP(Dot(point, plane.normal) - plane.distance, 0.0f);
}

bool PointInAABB(const Point& point, const physAABB& aabb) {
	Point min = GetMin(aabb);
	Point max = GetMax(aabb);

	if (point.x < min.x || point.y < min.y || point.z < min.z) {
		return false;
	}
	if (point.x > max.x || point.y > max.y || point.z > max.z) {
		return false;
	}

	return true;
}

bool PointInOBB(const Point& point, const OBB& obb) {
	physvec3 dir = point - obb.position;

	for (int i = 0; i < 3; ++i) {
		const float* orientation = &obb.orientation.asArray[i * 3];
		physvec3 axis(orientation[0], orientation[1], orientation[2]);

		float distance = Dot(dir, axis);

		if (distance > obb.size.asArray[i]) {
			return false;
		}
		if (distance < -obb.size.asArray[i]) {
			return false;
		}
	}

	return true;
}

Point ClosestPoint(const Sphere& sphere, const Point& point) {
	physvec3 sphereToPoint = point - sphere.position;
	Normalize(sphereToPoint);
	sphereToPoint = sphereToPoint * sphere.radius;
	return sphereToPoint + sphere.position;
}

Point ClosestPoint(const physAABB& aabb, const Point& point) {
	Point result = point;
	Point min = GetMin(aabb);
	Point max = GetMax(aabb);

	result.x = (result.x < min.x) ? min.x : result.x;
	result.y = (result.y < min.x) ? min.y : result.y;
	result.z = (result.z < min.x) ? min.z : result.z;

	result.x = (result.x > max.x) ? max.x : result.x;
	result.y = (result.y > max.x) ? max.y : result.y;
	result.z = (result.z > max.x) ? max.z : result.z;

	return result;
}

Point ClosestPoint(const OBB& obb, const Point& point) {
	Point result = obb.position;
	physvec3 dir = point - obb.position;

	for (int i = 0; i < 3; ++i) {
		const float* orientation = &obb.orientation.asArray[i * 3];
		physvec3 axis(orientation[0], orientation[1], orientation[2]);

		float distance = Dot(dir, axis);

		if (distance > obb.size.asArray[i]) {
			distance = obb.size.asArray[i];
		}
		if (distance < -obb.size.asArray[i]) {
			distance = -obb.size.asArray[i];
		}

		result = result + (axis * distance);
	}

	return result;
}

Point ClosestPoint(const Plane& plane, const Point& point) {
	// This works assuming plane.Normal is normalized, which it should be
	float distance = Dot(plane.normal, point) - plane.distance;
	// If the plane normal wasn't normalized, we'd need this:
	// distance = distance / DOT(plane.Normal, plane.Normal);

	return point - plane.normal * distance;
}

bool PointOnLine(const Point& point, const Line& line) {
	Point closest = ClosestPoint(line, point);
	float distanceSq = MagnitudeSq(closest - point);
	return CMP(distanceSq, 0.0f);
}

Point ClosestPoint(const Line& line, const Point& point) {
	physvec3 lVec = line.end - line.start; // Line Vector
										   // Project "point" onto the "Line Vector", computing:
										   // closest(t) = start + t * (end - start)
										   // T is how far along the line the projected point is
	float t = Dot(point - line.start, lVec) / Dot(lVec, lVec);
	// Clamp t to the 0 to 1 range
	t = fmaxf(t, 0.0f);
	t = fminf(t, 1.0f);
	// Return projected position of t
	return line.start + lVec * t;
}

bool PointOnRay(const Point& point, const physRay& ray) {
	if (point == ray.origin) {
		return true;
	}

	physvec3 norm = point - ray.origin;
	Normalize(norm);
	float diff = Dot(norm, ray.direction); // Direction is normalized
										   // If BOTH vectors point in the same direction, diff should be 1
	return CMP(diff, 1.0f);
}

Point ClosestPoint(const physRay& ray, const Point& point) {
	// Project point onto ray, 
	float t = Dot(point - ray.origin, ray.direction);
	// Not needed if direction is normalized!
	// t /= Dot(ray.direction, ray.direction);

	// We only want to clamp t in the positive direction.
	// The ray extends infinatley in this direction!
	t = fmaxf(t, 0.0f);

	// Compute the projected position from the clamped t
	// Notice we multiply r.Normal by t, not AB.
	// This is becuase we want the ray in the direction 
	// of the normal, which technically the line segment is
	// but this is much more explicit and easy to read.
	return Point(ray.origin + ray.direction * t);
}

bool PointInPlane(const Point& point, const Plane& plane) {
	return PointOnPlane(point, plane);
}
bool PointInLine(const Point& point, const Line& line) {
	return PointOnLine(point, line);
}
bool PointInRay(const Point& point, const physRay& ray) {
	return PointOnRay(point, ray);
}
bool ContainsPoint(const Sphere& sphere, const Point& point) {
	return PointInSphere(point, sphere);
}
bool ContainsPoint(const Point& point, const Sphere& sphere) {
	return PointInSphere(point, sphere);
}
bool ContainsPoint(const physAABB& aabb, const Point& point) {
	return PointInAABB(point, aabb);
}
bool ContainsPoint(const Point& point, const physAABB& aabb) {
	return PointInAABB(point, aabb);
}
bool ContainsPoint(const Point& point, const OBB& obb) {
	return PointInOBB(point, obb);
}
bool ContainsPoint(const OBB& obb, const Point& point) {
	return PointInOBB(point, obb);
}
bool ContainsPoint(const Point& point, const Plane& plane) {
	return PointOnPlane(point, plane);
}
bool ContainsPoint(const Plane& plane, const Point& point) {
	return PointOnPlane(point, plane);
}
bool ContainsPoint(const Point& point, const Line& line) {
	return PointOnLine(point, line);
}
bool ContainsPoint(const Line& line, const Point& point) {
	return PointOnLine(point, line);
}
bool ContainsPoint(const Point& point, const physRay& ray) {
	return PointOnRay(point, ray);
}
bool ContainsPoint(const physRay& ray, const Point& point) {
	return PointOnRay(point, ray);
}
Point ClosestPoint(const Point& point, const Sphere& sphere) {
	return ClosestPoint(sphere, point);
}
Point ClosestPoint(const Point& point, const physAABB& aabb) {
	return ClosestPoint(aabb, point);
}
Point ClosestPoint(const Point& point, const OBB& obb) {
	return ClosestPoint(obb, point);
}
Point ClosestPoint(const Point& point, const Plane& plane) {
	return ClosestPoint(plane, point);
}
Point ClosestPoint(const Point& point, const Line& line) {
	return ClosestPoint(line, point);
}
Point ClosestPoint(const Point& point, const physRay& ray) {
	return ClosestPoint(ray, point);
}
Point ClosestPoint(const Point& p, const Triangle& t) {
	return ClosestPoint(t, p);
}

bool SphereSphere(const Sphere& s1, const Sphere& s2) {
	float radiiSum = s1.radius + s2.radius;
	float sqDistance = MagnitudeSq(s1.position - s2.position);
	return sqDistance < radiiSum * radiiSum;
}

bool SphereAABB(const Sphere& sphere, const physAABB& aabb) {
	Point closestPoint = ClosestPoint(aabb, sphere.position);
	float distSq = MagnitudeSq(sphere.position - closestPoint);
	float radiusSq = sphere.radius * sphere.radius;
	return distSq < radiusSq;
}

bool SphereOBB(const Sphere& sphere, const OBB& obb) {
	Point closestPoint = ClosestPoint(obb, sphere.position);
	float distSq = MagnitudeSq(sphere.position - closestPoint);
	float radiusSq = sphere.radius * sphere.radius;
	return distSq < radiusSq;
}

bool SpherePlane(const Sphere& sphere, const Plane& plane) {
	Point closestPoint = ClosestPoint(plane, sphere.position);
	float distSq = MagnitudeSq(sphere.position - closestPoint);
	float radiusSq = sphere.radius * sphere.radius;
	return distSq < radiusSq;
}

bool AABBAABB(const physAABB& aabb1, const physAABB& aabb2) {
	Point aMin = GetMin(aabb1);
	Point aMax = GetMax(aabb1);
	Point bMin = GetMin(aabb2);
	Point bMax = GetMax(aabb2);

	return	(aMin.x <= bMax.x && aMax.x >= bMin.x) &&
		(aMin.y <= bMax.y && aMax.y >= bMin.y) &&
		(aMin.z <= bMax.z && aMax.z >= bMin.z);
}

bool AABBOBB(const physAABB& aabb, const OBB& obb) {
	const float* o = obb.orientation.asArray;

	physvec3 test[15] = {
		physvec3(1, 0, 0), // AABB axis 1
		physvec3(0, 1, 0), // AABB axis 2
		physvec3(0, 0, 1), // AABB axis 3
		physvec3(o[0], o[1], o[2]),
		physvec3(o[3], o[4], o[5]),
		physvec3(o[6], o[7], o[8])
	};

	for (int i = 0; i < 3; ++i) { // Fill out rest of axis
		test[6 + i * 3 + 0] = Cross(test[i], test[0]);
		test[6 + i * 3 + 1] = Cross(test[i], test[1]);
		test[6 + i * 3 + 2] = Cross(test[i], test[2]);
	}

	for (int i = 0; i < 15; ++i) {
		if (!OverlapOnAxis(aabb, obb, test[i])) {
			return false; // Seperating axis found
		}
	}

	return true; // Seperating axis not found
}

bool OverlapOnAxis(const physAABB& aabb, const OBB& obb, const physvec3& axis) {
	Interval a = GetInterval(aabb, axis);
	Interval b = GetInterval(obb, axis);
	return ((b.min <= a.max) && (a.min <= b.max));
}

bool OverlapOnAxis(const OBB& obb1, const OBB& obb2, const physvec3& axis) {
	Interval a = GetInterval(obb1, axis);
	Interval b = GetInterval(obb1, axis);
	return ((b.min <= a.max) && (a.min <= b.max));
}

bool OverlapOnAxis(const physAABB& aabb, const Triangle& triangle, const physvec3& axis) {
	Interval a = GetInterval(aabb, axis);
	Interval b = GetInterval(triangle, axis);
	return ((b.min <= a.max) && (a.min <= b.max));
}

bool OverlapOnAxis(const OBB& obb, const Triangle& triangle, const physvec3& axis) {
	Interval a = GetInterval(obb, axis);
	Interval b = GetInterval(triangle, axis);
	return ((b.min <= a.max) && (a.min <= b.max));
}

bool OverlapOnAxis(const Triangle& t1, const Triangle& t2, const physvec3& axis) {
	Interval a = GetInterval(t1, axis);
	Interval b = GetInterval(t2, axis);
	return ((b.min <= a.max) && (a.min <= b.max));
}

Interval GetInterval(const Triangle& triangle, const physvec3& axis) {
	Interval result;

	result.min = Dot(axis, triangle.points[0]);
	result.max = result.min;
	for (int i = 1; i < 3; ++i) {
		float value = Dot(axis, triangle.points[i]);
		result.min = fminf(result.min, value);
		result.max = fmaxf(result.max, value);
	}

	return result;
}

Interval GetInterval(const OBB& obb, const physvec3& axis) {
	physvec3 vertex[8];

	physvec3 C = obb.position;	// OBB Center
	physvec3 E = obb.size;		// OBB Extents
	const float* o = obb.orientation.asArray;
	physvec3 A[] = {			// OBB Axis
		physvec3(o[0], o[1], o[2]),
		physvec3(o[3], o[4], o[5]),
		physvec3(o[6], o[7], o[8]),
	};

	vertex[0] = C + A[0] * E[0] + A[1] * E[1] + A[2] * E[2];
	vertex[1] = C - A[0] * E[0] + A[1] * E[1] + A[2] * E[2];
	vertex[2] = C + A[0] * E[0] - A[1] * E[1] + A[2] * E[2];
	vertex[3] = C + A[0] * E[0] + A[1] * E[1] - A[2] * E[2];
	vertex[4] = C - A[0] * E[0] - A[1] * E[1] - A[2] * E[2];
	vertex[5] = C + A[0] * E[0] - A[1] * E[1] - A[2] * E[2];
	vertex[6] = C - A[0] * E[0] + A[1] * E[1] - A[2] * E[2];
	vertex[7] = C - A[0] * E[0] - A[1] * E[1] + A[2] * E[2];

	Interval result;
	result.min = result.max = Dot(axis, vertex[0]);

	for (int i = 1; i < 8; ++i) {
		float projection = Dot(axis, vertex[i]);
		result.min = (projection < result.min) ? projection : result.min;
		result.max = (projection > result.max) ? projection : result.max;
	}

	return result;
}

Interval GetInterval(const physAABB& aabb, const physvec3& axis) {
	physvec3 i = GetMin(aabb);
	physvec3 a = GetMax(aabb);

	physvec3 vertex[8] = {
		physvec3(i.x, a.y, a.z),
		physvec3(i.x, a.y, i.z),
		physvec3(i.x, i.y, a.z),
		physvec3(i.x, i.y, i.z),
		physvec3(a.x, a.y, a.z),
		physvec3(a.x, a.y, i.z),
		physvec3(a.x, i.y, a.z),
		physvec3(a.x, i.y, i.z)
	};

	Interval result;
	result.min = result.max = Dot(axis, vertex[0]);

	for (int i = 1; i < 8; ++i) {
		float projection = Dot(axis, vertex[i]);
		result.min = (projection < result.min) ? projection : result.min;
		result.max = (projection > result.max) ? projection : result.max;
	}

	return result;
}

bool AABBPlane(const physAABB& aabb, const Plane& plane) {
	// Project the half extents of the AABB onto the plane normal
	float pLen = aabb.size.x * fabsf(plane.normal.x) +
		aabb.size.y * fabsf(plane.normal.y) +
		aabb.size.z * fabsf(plane.normal.z);
	// Find the distance from the center of the AABB to the plane
	float dist = Dot(plane.normal, aabb.position) - plane.distance;
	// Intersection occurs if the distance falls within the projected side
	return fabsf(dist) <= pLen;
}

bool OBBOBB(const OBB& obb1, const OBB& obb2) {
	const float* o1 = obb1.orientation.asArray;
	const float* o2 = obb2.orientation.asArray;

	physvec3 test[15] = {
		physvec3(o1[0], o1[1], o1[2]),
		physvec3(o1[3], o1[4], o1[5]),
		physvec3(o1[6], o1[7], o1[8]),
		physvec3(o2[0], o2[1], o2[2]),
		physvec3(o2[3], o2[4], o2[5]),
		physvec3(o2[6], o2[7], o2[8])
	};

	for (int i = 0; i < 3; ++i) { // Fill out rest of axis
		test[6 + i * 3 + 0] = Cross(test[i], test[0]);
		test[6 + i * 3 + 1] = Cross(test[i], test[1]);
		test[6 + i * 3 + 2] = Cross(test[i], test[2]);
	}

	for (int i = 0; i < 15; ++i) {
		if (!OverlapOnAxis(obb1, obb2, test[i])) {
			return false; // Seperating axis found
		}
	}

	return true; // Seperating axis not found
}

bool OBBPlane(const OBB& obb, const Plane& plane) {
	// Local variables for readability only
	const float* o = obb.orientation.asArray;
	physvec3 rot[] = { // rotation / orientation
		physvec3(o[0], o[1], o[2]),
		physvec3(o[3], o[4], o[5]),
		physvec3(o[6], o[7], o[8]),
	};
	physvec3 normal = plane.normal;

	// Project the half extents of the AABB onto the plane normal
	float pLen = obb.size.x * fabsf(Dot(normal, rot[0])) +
		obb.size.y * fabsf(Dot(normal, rot[1])) +
		obb.size.z * fabsf(Dot(normal, rot[2]));
	// Find the distance from the center of the OBB to the plane
	float dist = Dot(plane.normal, obb.position) - plane.distance;
	// Intersection occurs if the distance falls within the projected side
	return fabsf(dist) <= pLen;
}

bool PlanePlane(const Plane& plane1, const Plane& plane2) {
	// Compute direction of intersection line
	physvec3 d = Cross(plane1.normal, plane2.normal);

	// Check the length of the direction line
	// if the length is 0, no intersection happened
	return !(CMP(Dot(d, d), 0));

	// We could have used the dot product here, instead of the cross product
}

bool Raycast(const Sphere& sphere, const physRay& ray, RaycastResult* outResult) {
	ResetRaycastResult(outResult);

	physvec3 e = sphere.position - ray.origin;
	float rSq = sphere.radius * sphere.radius;

	float eSq = MagnitudeSq(e);
	float a = Dot(e, ray.direction); // ray.direction is assumed to be normalized
	float bSq = /*sqrtf(*/eSq - (a * a)/*)*/;
	float f = sqrt(fabsf((rSq)- /*(b * b)*/bSq));

	// Assume normal intersection!
	float t = a - f;

	// No collision has happened
	if (rSq - (eSq - a * a) < 0.0f) {
		return false;
	}
	// Ray starts inside the sphere
	else if (eSq < rSq) {
		// Just reverse direction
		t = a + f;
	}
	if (outResult != 0) {
		outResult->t = t;
		outResult->hit = true;
		outResult->point = ray.origin + ray.direction * t;
		outResult->normal = Normalized(outResult->point - sphere.position);
	}
	return true;
}

bool Raycast(const OBB& obb, const physRay& ray, RaycastResult* outResult) {
	ResetRaycastResult(outResult);

	const float* o = obb.orientation.asArray;
	const float* size = obb.size.asArray;

	physvec3 p = obb.position - ray.origin;

	physvec3 X(o[0], o[1], o[2]);
	physvec3 Y(o[3], o[4], o[5]);
	physvec3 Z(o[6], o[7], o[8]);

	physvec3 f(
		Dot(X, ray.direction),
		Dot(Y, ray.direction),
		Dot(Z, ray.direction)
	);

	physvec3 e(
		Dot(X, p),
		Dot(Y, p),
		Dot(Z, p)
	);

#if 1
	float t[6] = { 0, 0, 0, 0, 0, 0 };
	for (int i = 0; i < 3; ++i) {
		if (CMP(f[i], 0)) {
			if (-e[i] - size[i] > 0 || -e[i] + size[i] < 0) {
				return false;
			}
			f[i] = 0.00001f; // Avoid div by 0!
		}

		t[i * 2 + 0] = (e[i] + size[i]) / f[i]; // tmin[x, y, z]
		t[i * 2 + 1] = (e[i] - size[i]) / f[i]; // tmax[x, y, z]
	}

	float tmin = fmaxf(fmaxf(fminf(t[0], t[1]), fminf(t[2], t[3])), fminf(t[4], t[5]));
	float tmax = fminf(fminf(fmaxf(t[0], t[1]), fmaxf(t[2], t[3])), fmaxf(t[4], t[5]));
#else 
	// The above loop simplifies the below if statements
	// this is done to make sure the sample fits into the book
	if (CMP(f.x, 0)) {
		if (-e.x - obb.size.x > 0 || -e.x + obb.size.x < 0) {
			return -1;
		}
		f.x = 0.00001f; // Avoid div by 0!
	}
	else if (CMP(f.y, 0)) {
		if (-e.y - obb.size.y > 0 || -e.y + obb.size.y < 0) {
			return -1;
		}
		f.y = 0.00001f; // Avoid div by 0!
	}
	else if (CMP(f.z, 0)) {
		if (-e.z - obb.size.z > 0 || -e.z + obb.size.z < 0) {
			return -1;
		}
		f.z = 0.00001f; // Avoid div by 0!
	}

	float t1 = (e.x + obb.size.x) / f.x;
	float t2 = (e.x - obb.size.x) / f.x;
	float t3 = (e.y + obb.size.y) / f.y;
	float t4 = (e.y - obb.size.y) / f.y;
	float t5 = (e.z + obb.size.z) / f.z;
	float t6 = (e.z - obb.size.z) / f.z;

	float tmin = fmaxf(fmaxf(fminf(t1, t2), fminf(t3, t4)), fminf(t5, t6));
	float tmax = fminf(fminf(fmaxf(t1, t2), fmaxf(t3, t4)), fmaxf(t5, t6));
#endif

	// if tmax < 0, ray is intersecting AABB
	// but entire AABB is behing it's origin
	if (tmax < 0) {
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax) {
		return false;
	}

	// If tmin is < 0, tmax is closer
	float t_result = tmin;

	if (tmin < 0.0f) {
		t_result = tmax;
	}

	if (outResult != 0) {
		outResult->hit = true;
		outResult->t = t_result;
		outResult->point = ray.origin + ray.direction * t_result;

		physvec3 normals[] = {
			X,			// +x
			X * -1.0f,	// -x
			Y,			// +y
			Y * -1.0f,	// -y
			Z,			// +z
			Z * -1.0f	// -z
		};

		for (int i = 0; i < 6; ++i) {
			if (CMP(t_result, t[i])) {
				outResult->normal = Normalized(normals[i]);
			}
		}
	}
	return true;
}

void ResetRaycastResult(RaycastResult* outResult) {
	if (outResult != 0) {
		outResult->t = -1;
		outResult->hit = false;
		outResult->normal = physvec3(0, 0, 1);
		outResult->point = physvec3(0, 0, 0);
	}
}

bool Raycast(const physAABB& aabb, const physRay& ray, RaycastResult* outResult) {
	ResetRaycastResult(outResult);

	physvec3 min = GetMin(aabb);
	physvec3 max = GetMax(aabb);

	// Any component of direction could be 0!
	// Address this by using a small number, close to
	// 0 in case any of directions components are 0
	float t1 = (min.x - ray.origin.x) / (CMP(ray.direction.x, 0.0f) ? 0.00001f : ray.direction.x);
	float t2 = (max.x - ray.origin.x) / (CMP(ray.direction.x, 0.0f) ? 0.00001f : ray.direction.x);
	float t3 = (min.y - ray.origin.y) / (CMP(ray.direction.y, 0.0f) ? 0.00001f : ray.direction.y);
	float t4 = (max.y - ray.origin.y) / (CMP(ray.direction.y, 0.0f) ? 0.00001f : ray.direction.y);
	float t5 = (min.z - ray.origin.z) / (CMP(ray.direction.z, 0.0f) ? 0.00001f : ray.direction.z);
	float t6 = (max.z - ray.origin.z) / (CMP(ray.direction.z, 0.0f) ? 0.00001f : ray.direction.z);

	float tmin = fmaxf(fmaxf(fminf(t1, t2), fminf(t3, t4)), fminf(t5, t6));
	float tmax = fminf(fminf(fmaxf(t1, t2), fmaxf(t3, t4)), fmaxf(t5, t6));

	// if tmax < 0, ray is intersecting AABB
	// but entire AABB is behing it's origin
	if (tmax < 0) {
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax) {
		return false;
	}

	float t_result = tmin;

	// If tmin is < 0, tmax is closer
	if (tmin < 0.0f) {
		t_result = tmax;
	}

	if (outResult != 0) {
		outResult->t = t_result;
		outResult->hit = true;
		outResult->point = ray.origin + ray.direction * t_result;

		physvec3 normals[] = {
			physvec3(-1, 0, 0),
			physvec3(1, 0, 0),
			physvec3(0, -1, 0),
			physvec3(0, 1, 0),
			physvec3(0, 0, -1),
			physvec3(0, 0, 1)
		};
		float t[] = { t1, t2, t3, t4, t5, t6 };

		for (int i = 0; i < 6; ++i) {
			if (CMP(t_result, t[i])) {
				outResult->normal = normals[i];
			}
		}
	}

	return true;
}

bool Raycast(const Plane& plane, const physRay& ray, RaycastResult* outResult) {
	ResetRaycastResult(outResult);

	float nd = Dot(ray.direction, plane.normal);
	float pn = Dot(ray.origin, plane.normal);

	// nd must be negative, and not 0
	// if nd is positive, the ray and plane normals
	// point in the same direction. No intersection.
	if (nd >= 0.0f) {
		return false;
	}

	float t = (plane.distance - pn) / nd;

	// t must be positive
	if (t >= 0.0f) {
		if (outResult != 0) {
			outResult->t = t;
			outResult->hit = true;
			outResult->point = ray.origin + ray.direction * t;
			outResult->normal = Normalized(plane.normal);
		}
		return true;
	}

	return false;
}

bool Linetest(const Sphere& sphere, const Line& line) {
	Point closest = ClosestPoint(line, sphere.position);
	float distSq = MagnitudeSq(sphere.position - closest);
	return distSq <= (sphere.radius * sphere.radius);
}

bool Linetest(const Plane& plane, const Line& line) {
	physvec3 ab = line.end - line.start;

	float nA = Dot(plane.normal, line.start);
	float nAB = Dot(plane.normal, ab);

	if (CMP(nAB, 0)) {
		return false;
	}

	float t = (plane.distance - nA) / nAB;
	return t >= 0.0f && t <= 1.0f;
}

bool Linetest(const physAABB& aabb, const Line& line) {
	physRay ray;
	ray.origin = line.start;
	ray.direction = Normalized(line.end - line.start);
	RaycastResult raycast;
	if (!Raycast(aabb, ray, &raycast)) {
		return false;
	}
	float t = raycast.t;

	return t >= 0 && t * t <= LengthSq(line);
}

bool Linetest(const OBB& obb, const Line& line) {
	if (MagnitudeSq(line.end - line.start) < 0.0000001f) {
		return PointInOBB(line.start, obb);
	}
	physRay ray;
	ray.origin = line.start;
	ray.direction = Normalized(line.end - line.start);
	RaycastResult result;
	if (!Raycast(obb, ray, &result)) {
		return false;
	}
	float t = result.t;

	return t >= 0 && t * t <= LengthSq(line);
}

bool Raycast(const physRay& ray, const Sphere& sphere, RaycastResult* outResult) {
	return Raycast(sphere, ray, outResult);
}

bool Raycast(const physRay& ray, const physAABB& aabb, RaycastResult* outResult) {
	return Raycast(aabb, ray, outResult);
}

bool Raycast(const physRay& ray, const OBB& obb, RaycastResult* outResult) {
	return Raycast(obb, ray, outResult);
}

bool Raycast(const physRay& ray, const Plane& plane, RaycastResult* outResult) {
	return Raycast(plane, ray, outResult);
}

bool Linetest(const Line& line, const Sphere& sphere) {
	return Linetest(sphere, line);
}

bool Linetest(const Line& line, const physAABB& aabb) {
	return Linetest(aabb, line);
}

bool Linetest(const Line& line, const OBB& obb) {
	return Linetest(obb, line);
}

bool Linetest(const Line& line, const Plane& plane) {
	return Linetest(plane, line);
}

physvec3 Centroid(const Triangle& t) {
	physvec3 result;
	result.x = t.a.x + t.b.x + t.c.x;
	result.y = t.a.y + t.b.y + t.c.y;
	result.z = t.a.z + t.b.z + t.c.z;
	result = result * (1.0f / 3.0f);
	return result;
}

bool PointInTriangle(const Point& p, const Triangle& t) {
	// Move the triangle so that the point is  
	// now at the origin of the triangle
	physvec3 a = t.a - p;
	physvec3 b = t.b - p;
	physvec3 c = t.c - p;

	// The point should be moved too, so they are both
	// relative, but because we don't use p in the
	// equation anymore, we don't need it!
	// p -= p; // This would just equal the zero vector!

	physvec3 normPBC = Cross(b, c); // Normal of PBC (u)
	physvec3 normPCA = Cross(c, a); // Normal of PCA (v)
	physvec3 normPAB = Cross(a, b); // Normal of PAB (w)

									// Test to see if the normals are facing 
									// the same direction, return false if not
	if (Dot(normPBC, normPCA) < 0.0f) {
		return false;
	}
	else if (Dot(normPBC, normPAB) < 0.0f) {
		return false;
	}

	// All normals facing the same way, return true
	return true;
}

physvec3 BarycentricOptimized(const Point& p, const Triangle& t) {
	physvec3 v0 = t.b - t.a;
	physvec3 v1 = t.c - t.a;
	physvec3 v2 = p - t.a;

	float d00 = Dot(v0, v0);
	float d01 = Dot(v0, v1);
	float d11 = Dot(v1, v1);
	float d20 = Dot(v2, v0);
	float d21 = Dot(v2, v1);
	float denom = d00 * d11 - d01 * d01;

	if (CMP(denom, 0.0f)) {
		return physvec3();
	}

	physvec3 result;
	result.y = (d11 * d20 - d01 * d21) / denom;
	result.z = (d00 * d21 - d01 * d20) / denom;
	result.x = 1.0f - result.y - result.z;

	return result;
}

physvec3 Barycentric(const Point& p, const Triangle& t) {
	physvec3 ap = p - t.a;
	physvec3 bp = p - t.b;
	physvec3 cp = p - t.c;

	physvec3 ab = t.b - t.a;
	physvec3 ac = t.c - t.a;
	physvec3 bc = t.c - t.b;
	physvec3 cb = t.b - t.c;
	physvec3 ca = t.a - t.c;

	physvec3 v = ab - Project(ab, cb);
	float a = 1.0f - (Dot(v, ap) / Dot(v, ab));

	v = bc - Project(bc, ac);
	float b = 1.0f - (Dot(v, bp) / Dot(v, bc));

	v = ca - Project(ca, ab);
	float c = 1.0f - (Dot(v, cp) / Dot(v, ca));

	return physvec3(a, b, c);
}

Plane FromTriangle(const Triangle& t) {
	Plane result;
	result.normal = Normalized(Cross(t.b - t.a, t.c - t.a));
	result.distance = Dot(result.normal, t.a);
	return result;
}

Point ClosestPoint(const Triangle& t, const Point& p) {
	Plane plane = FromTriangle(t);
	Point closest = ClosestPoint(plane, p);

	// Closest point was inside triangle
	if (PointInTriangle(closest, t)) {
		return closest;
	}

	Point c1 = ClosestPoint(Line(t.a, t.b), closest); // Line AB
	Point c2 = ClosestPoint(Line(t.b, t.c), closest); // Line BC
	Point c3 = ClosestPoint(Line(t.c, t.a), closest); // Line CA

	float magSq1 = MagnitudeSq(closest - c1);
	float magSq2 = MagnitudeSq(closest - c2);
	float magSq3 = MagnitudeSq(closest - c3);

	if (magSq1 < magSq2 && magSq1 < magSq3) {
		return c1;
	}
	else if (magSq2 < magSq1 && magSq2 < magSq3) {
		return c2;
	}

	return c3;
}

bool TriangleSphere(const Triangle& t, const Sphere& s) {
	Point closest = ClosestPoint(t, s.position);
	float magSq = MagnitudeSq(closest - s.position);
	return magSq <= s.radius * s.radius;
}

bool TriangleAABB(const Triangle& t, const physAABB& a) {
	// Compute the edge vectors of the triangle  (ABC)
	physvec3 f0 = t.b - t.a;
	physvec3 f1 = t.c - t.b;
	physvec3 f2 = t.a - t.c;

	// Compute the face normals of the AABB
	physvec3 u0(1.0f, 0.0f, 0.0f);
	physvec3 u1(0.0f, 1.0f, 0.0f);
	physvec3 u2(0.0f, 0.0f, 1.0f);

	physvec3 test[13] = {
		// 3 Normals of AABB
		u0, // AABB Axis 1
		u1, // AABB Axis 2
		u2, // AABB Axis 3
			// 1 Normal of the Triangle
			Cross(f0, f1),
			// 9 Axis, cross products of all edges
			Cross(u0, f0),
			Cross(u0, f1),
			Cross(u0, f2),
			Cross(u1, f0),
			Cross(u1, f1),
			Cross(u1, f2),
			Cross(u2, f0),
			Cross(u2, f1),
			Cross(u2, f2)
	};

	for (int i = 0; i < 13; ++i) {
		if (!OverlapOnAxis(a, t, test[i])) {
			return false; // Seperating axis found
		}
	}

	return true; // Seperating axis not found
}

bool TriangleOBB(const Triangle& t, const OBB& o) {
	// Compute the edge vectors of the triangle  (ABC)
	physvec3 f0 = t.b - t.a;
	physvec3 f1 = t.c - t.b;
	physvec3 f2 = t.a - t.c;

	// Compute the face normals of the AABB
	const float* orientation = o.orientation.asArray;
	physvec3 u0(orientation[0], orientation[1], orientation[2]);
	physvec3 u1(orientation[3], orientation[4], orientation[5]);
	physvec3 u2(orientation[6], orientation[7], orientation[8]);

	physvec3 test[13] = {
		// 3 Normals of AABB
		u0, // AABB Axis 1
		u1, // AABB Axis 2
		u2, // AABB Axis 3
			// 1 Normal of the Triangle
			Cross(f0, f1),
			// 9 Axis, cross products of all edges
			Cross(u0, f0),
			Cross(u0, f1),
			Cross(u0, f2),
			Cross(u1, f0),
			Cross(u1, f1),
			Cross(u1, f2),
			Cross(u2, f0),
			Cross(u2, f1),
			Cross(u2, f2)
	};

	for (int i = 0; i < 13; ++i) {
		if (!OverlapOnAxis(o, t, test[i])) {
			return false; // Seperating axis found
		}
	}

	return true; // Seperating axis not found
}

bool TriangleTriangle(const Triangle& t1, const Triangle& t2) {
#if 0
	vec3 axisToTest[] = {
		// Triangle 1, Normal
		SatCrossEdge(t1.a, t1.b, t1.b, t1.c),
		// Triangle 2, Normal
		SatCrossEdge(t2.a, t2.b, t2.b, t2.c),

		// Cross Product of edges
		SatCrossEdge(t2.a, t2.b, t1.a, t1.b),
		SatCrossEdge(t2.a, t2.b, t1.b, t1.c),
		SatCrossEdge(t2.a, t2.b, t1.c, t1.a),

		SatCrossEdge(t2.b, t2.c, t1.a, t1.b),
		SatCrossEdge(t2.b, t2.c, t1.b, t1.c),
		SatCrossEdge(t2.b, t2.c, t1.c, t1.a),

		SatCrossEdge(t2.c, t2.a, t1.a, t1.b),
		SatCrossEdge(t2.c, t2.a, t1.b, t1.c),
		SatCrossEdge(t2.c, t2.a, t1.c, t1.a),
	};
#else 
	physvec3 t1_f0 = t1.b - t1.a; // Edge 0
	physvec3 t1_f1 = t1.c - t1.b; // Edge 1
	physvec3 t1_f2 = t1.a - t1.c; // Edge 2

	physvec3 t2_f0 = t2.b - t2.a; // Edge 0
	physvec3 t2_f1 = t2.c - t2.b; // Edge 1
	physvec3 t2_f2 = t2.a - t2.c; // Edge 2

	physvec3 axisToTest[] = {
		// Triangle 1, Normal
		Cross(t1_f0, t1_f1),
		// Triangle 2, Normal
		Cross(t2_f0, t2_f1),

		// Cross Product of edges
		Cross(t2_f0, t1_f0),
		Cross(t2_f0, t1_f1),
		Cross(t2_f0, t1_f2),

		Cross(t2_f1, t1_f0),
		Cross(t2_f1, t1_f1),
		Cross(t2_f1, t1_f2),

		Cross(t2_f2, t1_f0),
		Cross(t2_f2, t1_f1),
		Cross(t2_f2, t1_f2),
	};
#endif

	for (int i = 0; i < 11; ++i) {
		if (!OverlapOnAxis(t1, t2, axisToTest[i])) {
			return false; // Seperating axis found
		}
	}

	return true; // Seperating axis not found
}

bool TriangleTriangleRobust(const Triangle& t1, const Triangle& t2) {
	physvec3 axisToTest[] = {
		// Triangle 1, Normal
		SatCrossEdge(t1.a, t1.b, t1.b, t1.c),
		// Triangle 2, Normal
		SatCrossEdge(t2.a, t2.b, t2.b, t2.c),

		// Cross Product of edges
		SatCrossEdge(t2.a, t2.b, t1.a, t1.b),
		SatCrossEdge(t2.a, t2.b, t1.b, t1.c),
		SatCrossEdge(t2.a, t2.b, t1.c, t1.a),

		SatCrossEdge(t2.b, t2.c, t1.a, t1.b),
		SatCrossEdge(t2.b, t2.c, t1.b, t1.c),
		SatCrossEdge(t2.b, t2.c, t1.c, t1.a),

		SatCrossEdge(t2.c, t2.a, t1.a, t1.b),
		SatCrossEdge(t2.c, t2.a, t1.b, t1.c),
		SatCrossEdge(t2.c, t2.a, t1.c, t1.a),
	};

	for (int i = 0; i < 11; ++i) {
		if (!OverlapOnAxis(t1, t2, axisToTest[i])) {
			if (!CMP(MagnitudeSq(axisToTest[i]), 0)) {
				return false; // Seperating axis found
			}
		}
	}

	return true; // Seperating axis not found
}

physvec3 SatCrossEdge(const physvec3& a, const physvec3& b, const physvec3& c, const physvec3& d) {
	physvec3 ab = b - a;
	physvec3 cd = d - c;

	physvec3 result = Cross(ab, cd);
	if (!CMP(MagnitudeSq(result), 0)) { // Is ab and cd parallel?
		return result; // Not parallel!
	}
	else { // ab and cd are parallel
		   // Get an axis perpendicular to AB
		physvec3 axis = Cross(ab, c - a);
		result = Cross(ab, axis);
		if (!CMP(MagnitudeSq(result), 0)) { // Still parallel?
			return result; // Not parallel
		}
	}
	// New axis being tested is parallel too.
	// This means that a, b, c and d are on a line
	// Nothing we can do!
	return physvec3();
}

Point debugRaycastResult;

bool Raycast(const Triangle& triangle, const physRay& ray, RaycastResult* outResult) {
	ResetRaycastResult(outResult);
	Plane plane = FromTriangle(triangle);

	RaycastResult planeResult;
	if (!Raycast(plane, ray, &planeResult)) {
		return false;
	}
	float t = planeResult.t;

	Point result = ray.origin + ray.direction * t;

	physvec3 barycentric = Barycentric(result, triangle);
	if (barycentric.x >= 0.0f && barycentric.x <= 1.0f &&
		barycentric.y >= 0.0f && barycentric.y <= 1.0f &&
		barycentric.z >= 0.0f && barycentric.z <= 1.0f) {

		if (outResult != 0) {
			outResult->t = t;
			outResult->hit = true;
			outResult->point = ray.origin + ray.direction * t;
			outResult->normal = plane.normal;
		}

		return true;
	}

	return false;
}

bool Linetest(const Triangle& triangle, const Line& line) {
	physRay ray;
	ray.origin = line.start;
	ray.direction = Normalized(line.end - line.start);
	RaycastResult raycast;
	if (!Raycast(triangle, ray, &raycast)) {
		return false;
	}
	float t = raycast.t;

	return t >= 0 && t * t <= LengthSq(line);
}

void AccelerateMesh(physMesh& mesh) {
	if (mesh.accelerator != 0) {
		return;
	}

	physvec3 min = mesh.vertices[0];
	physvec3 max = mesh.vertices[0];

	for (int i = 1; i < mesh.numTriangles * 3; ++i) {
		min.x = fminf(mesh.vertices[i].x, min.x);
		min.y = fminf(mesh.vertices[i].y, min.y);
		min.z = fminf(mesh.vertices[i].z, min.z);

		max.x = fmaxf(mesh.vertices[i].x, max.x);
		max.y = fmaxf(mesh.vertices[i].y, max.y);
		max.z = fmaxf(mesh.vertices[i].z, max.z);
	}

	mesh.accelerator = new BVHNode();
	mesh.accelerator->bounds = FromMinMax(min, max);
	mesh.accelerator->children = 0;
	mesh.accelerator->numTriangles = mesh.numTriangles;
	mesh.accelerator->triangles = new int[mesh.numTriangles];
	for (int i = 0; i < mesh.numTriangles; ++i) {
		mesh.accelerator->triangles[i] = i;
	}

	SplitBVHNode(mesh.accelerator, mesh, 3);
}

void SplitBVHNode(BVHNode* node, const physMesh& model, int depth) {
	if (depth-- <= 0) { // Decrements depth
		return;
	}

	if (node->children == 0) {
		// Only split if this node contains triangles
		if (node->numTriangles > 0) {
			node->children = new BVHNode[8];

			physvec3 c = node->bounds.position;
			physvec3 e = node->bounds.size *0.5f;

			node->children[0].bounds = physAABB(c + physvec3(-e.x, +e.y, -e.z), e);
			node->children[1].bounds = physAABB(c + physvec3(+e.x, +e.y, -e.z), e);
			node->children[2].bounds = physAABB(c + physvec3(-e.x, +e.y, +e.z), e);
			node->children[3].bounds = physAABB(c + physvec3(+e.x, +e.y, +e.z), e);
			node->children[4].bounds = physAABB(c + physvec3(-e.x, -e.y, -e.z), e);
			node->children[5].bounds = physAABB(c + physvec3(+e.x, -e.y, -e.z), e);
			node->children[6].bounds = physAABB(c + physvec3(-e.x, -e.y, +e.z), e);
			node->children[7].bounds = physAABB(c + physvec3(+e.x, -e.y, +e.z), e);

		}
	}

	// If this node was just split
	if (node->children != 0 && node->numTriangles > 0) {
		for (int i = 0; i < 8; ++i) { // For each child
									  // Count how many triangles each child will contain
			node->children[i].numTriangles = 0;
			for (int j = 0; j < node->numTriangles; ++j) {
				Triangle t = model.triangles[node->triangles[j]];
				if (TriangleAABB(t, node->children[i].bounds)) {
					node->children[i].numTriangles += 1;
				}
			}
			if (node->children[i].numTriangles == 0) {
				continue;
			}
			node->children[i].triangles = new int[node->children[i].numTriangles];
			int index = 0; // Add the triangles in the new child arrau
			for (int j = 0; j < node->numTriangles; ++j) {
				Triangle t = model.triangles[node->triangles[j]];
				if (TriangleAABB(t, node->children[i].bounds)) {
					node->children[i].triangles[index++] = node->triangles[j];
				}
			}
		}

		node->numTriangles = 0;
		delete[] node->triangles;
		node->triangles = 0;

		// Recurse
		for (int i = 0; i < 8; ++i) {
			SplitBVHNode(&node->children[i], model, depth);
		}
	}
}

void FreeBVHNode(BVHNode* node) {
	if (node->children != 0) {
		for (int i = 0; i < 8; ++i) {
			FreeBVHNode(&node->children[i]);
		}
		delete[] node->children;
		node->children = 0;
	}

	if (node->numTriangles != 0 || node->triangles != 0) {
		delete[] node->triangles;
		node->triangles = 0;
		node->numTriangles = 0;
	}
}

bool MeshAABB(const physMesh& mesh, const physAABB& aabb) {
	if (mesh.accelerator == 0) {
		for (int i = 0; i < mesh.numTriangles; ++i) {
			if (TriangleAABB(mesh.triangles[i], aabb)) {
				return true;
			}
		}
	}
	else {
		std::list<BVHNode*> toProcess;
		toProcess.push_front(mesh.accelerator);

		// Recursivley walk the BVH tree
		while (!toProcess.empty()) {
			BVHNode* iterator = *(toProcess.begin());
			toProcess.erase(toProcess.begin());

			if (iterator->numTriangles >= 0) {
				// Iterate trough all triangles of the node
				for (int i = 0; i < iterator->numTriangles; ++i) {
					// Triangle indices in BVHNode index the mesh
					if (TriangleAABB(mesh.triangles[iterator->triangles[i]], aabb)) {
						return true;
					}
				}
			}

			if (iterator->children != 0) {
				for (int i = 8 - 1; i >= 0; --i) {
					// Only push children whos bounds intersect the test geometry
					if (AABBAABB(iterator->children[i].bounds, aabb)) {
						toProcess.push_front(&iterator->children[i]);
					}
				}
			}
		}
	}
	return false;
}

bool Linetest(const physMesh& mesh, const Line& line) {
	if (mesh.accelerator == 0) {
		for (int i = 0; i < mesh.numTriangles; ++i) {
			if (Linetest(mesh.triangles[i], line)) {
				return true;
			}
		}
	}
	else {
		std::list<BVHNode*> toProcess;
		toProcess.push_front(mesh.accelerator);

		// Recursivley walk the BVH tree
		while (!toProcess.empty()) {
			BVHNode* iterator = *(toProcess.begin());
			toProcess.erase(toProcess.begin());

			if (iterator->numTriangles >= 0) {
				// Iterate trough all triangles of the node
				for (int i = 0; i < iterator->numTriangles; ++i) {
					// Triangle indices in BVHNode index the mesh
					if (Linetest(mesh.triangles[iterator->triangles[i]], line)) {
						return true;
					}
				}
			}

			if (iterator->children != 0) {
				for (int i = 8 - 1; i >= 0; --i) {
					// Only push children whos bounds intersect the test geometry
					if (Linetest(iterator->children[i].bounds, line)) {
						toProcess.push_front(&iterator->children[i]);
					}
				}
			}
		}
	}
	return false;
}

bool MeshSphere(const physMesh& mesh, const Sphere& sphere) {
	if (mesh.accelerator == 0) {
		for (int i = 0; i < mesh.numTriangles; ++i) {
			if (TriangleSphere(mesh.triangles[i], sphere)) {
				return true;
			}
		}
	}
	else {
		std::list<BVHNode*> toProcess;
		toProcess.push_front(mesh.accelerator);

		// Recursivley walk the BVH tree
		while (!toProcess.empty()) {
			BVHNode* iterator = *(toProcess.begin());
			toProcess.erase(toProcess.begin());

			if (iterator->numTriangles >= 0) {
				// Iterate trough all triangles of the node
				for (int i = 0; i < iterator->numTriangles; ++i) {
					// Triangle indices in BVHNode index the mesh
					if (TriangleSphere(mesh.triangles[iterator->triangles[i]], sphere)) {
						return true;
					}
				}
			}

			if (iterator->children != 0) {
				for (int i = 8 - 1; i >= 0; --i) {
					// Only push children whos bounds intersect the test geometry
					if (SphereAABB(sphere, iterator->children[i].bounds)) {
						toProcess.push_front(&iterator->children[i]);
					}
				}
			}
		}
	}
	return false;
}

bool MeshOBB(const physMesh& mesh, const OBB& obb) {
	if (mesh.accelerator == 0) {
		for (int i = 0; i < mesh.numTriangles; ++i) {
			if (TriangleOBB(mesh.triangles[i], obb)) {
				return true;
			}
		}
	}
	else {
		std::list<BVHNode*> toProcess;
		toProcess.push_front(mesh.accelerator);

		// Recursivley walk the BVH tree
		while (!toProcess.empty()) {
			BVHNode* iterator = *(toProcess.begin());
			toProcess.erase(toProcess.begin());

			if (iterator->numTriangles >= 0) {
				// Iterate trough all triangles of the node
				for (int i = 0; i < iterator->numTriangles; ++i) {
					// Triangle indices in BVHNode index the mesh
					if (TriangleOBB(mesh.triangles[iterator->triangles[i]], obb)) {
						return true;
					}
				}
			}

			if (iterator->children != 0) {
				for (int i = 8 - 1; i >= 0; --i) {
					// Only push children whos bounds intersect the test geometry
					if (AABBOBB(iterator->children[i].bounds, obb)) {
						toProcess.push_front(&iterator->children[i]);
					}
				}
			}
		}
	}
	return false;
}

bool MeshPlane(const physMesh& mesh, const Plane& plane) {
	if (mesh.accelerator == 0) {
		for (int i = 0; i < mesh.numTriangles; ++i) {
			if (TrianglePlane(mesh.triangles[i], plane)) {
				return true;
			}
		}
	}
	else {
		std::list<BVHNode*> toProcess;
		toProcess.push_front(mesh.accelerator);

		// Recursivley walk the BVH tree
		while (!toProcess.empty()) {
			BVHNode* iterator = *(toProcess.begin());
			toProcess.erase(toProcess.begin());

			if (iterator->numTriangles >= 0) {
				// Iterate trough all triangles of the node
				for (int i = 0; i < iterator->numTriangles; ++i) {
					// Triangle indices in BVHNode index the mesh
					if (TrianglePlane(mesh.triangles[iterator->triangles[i]], plane)) {
						return true;
					}
				}
			}

			if (iterator->children != 0) {
				for (int i = 8 - 1; i >= 0; --i) {
					// Only push children whos bounds intersect the test geometry
					if (AABBPlane(iterator->children[i].bounds, plane)) {
						toProcess.push_front(&iterator->children[i]);
					}
				}
			}
		}
	}
	return false;
}

bool MeshTriangle(const physMesh& mesh, const Triangle& triangle) {
	if (mesh.accelerator == 0) {
		for (int i = 0; i < mesh.numTriangles; ++i) {
			if (TriangleTriangle(mesh.triangles[i], triangle)) {
				return true;
			}
		}
	}
	else {
		std::list<BVHNode*> toProcess;
		toProcess.push_front(mesh.accelerator);

		// Recursivley walk the BVH tree
		while (!toProcess.empty()) {
			BVHNode* iterator = *(toProcess.begin());
			toProcess.erase(toProcess.begin());

			if (iterator->numTriangles >= 0) {
				// Iterate trough all triangles of the node
				for (int i = 0; i < iterator->numTriangles; ++i) {
					// Triangle indices in BVHNode index the mesh
					if (TriangleTriangle(mesh.triangles[iterator->triangles[i]], triangle)) {
						return true;
					}
				}
			}

			if (iterator->children != 0) {
				for (int i = 8 - 1; i >= 0; --i) {
					// Only push children whos bounds intersect the test geometry
					if (TriangleAABB(triangle, iterator->children[i].bounds)) {
						toProcess.push_front(&iterator->children[i]);
					}
				}
			}
		}
	}
	return false;
}

float Raycast(const physMesh& mesh, const physRay& ray) {
	return MeshRay(mesh, ray);
}

float Raycast(const physModel& mesh, const physRay& ray) {
	return ModelRay(mesh, ray);
}

float MeshRay(const physMesh& mesh, const physRay& ray) {
	if (mesh.accelerator == 0) {
		for (int i = 0; i < mesh.numTriangles; ++i) {
			RaycastResult raycast;
			Raycast(mesh.triangles[i], ray, &raycast);
			float result = raycast.t;
			if (result >= 0) {
				return result;
			}
		}
	}
	else {
		std::list<BVHNode*> toProcess;
		toProcess.push_front(mesh.accelerator);

		// Recursivley walk the BVH tree
		while (!toProcess.empty()) {
			BVHNode* iterator = *(toProcess.begin());
			toProcess.erase(toProcess.begin());

			if (iterator->numTriangles >= 0) {
				// Iterate trough all triangles of the node
				for (int i = 0; i < iterator->numTriangles; ++i) {
					// Triangle indices in BVHNode index the mesh
					RaycastResult raycast;
					Raycast(mesh.triangles[iterator->triangles[i]], ray, &raycast);
					float r = raycast.t;
					if (r >= 0) {
						return r;
					}
				}
			}

			if (iterator->children != 0) {
				for (int i = 8 - 1; i >= 0; --i) {
					// Only push children whos bounds intersect the test geometry
					RaycastResult raycast;
					Raycast(iterator->children[i].bounds, ray, &raycast);
					if (raycast.t >= 0) {
						toProcess.push_front(&iterator->children[i]);
					}
				}
			}
		}
	}
	return -1;
}

bool TrianglePlane(const Triangle& t, const Plane& p) {
	float side1 = PlaneEquation(t.a, p);
	float side2 = PlaneEquation(t.b, p);
	float side3 = PlaneEquation(t.c, p);

	// On Plane
	if (CMP(side1, 0) && CMP(side2, 0) && CMP(side3, 0)) {
		return true;
	}

	// Triangle in front of plane
	if (side1 > 0 && side2 > 0 && side3 > 0) {
		return false;
	}

	// Triangle behind plane
	if (side1 < 0 && side2 < 0 && side3 < 0) {
		return false;
	}

	return true; // Intersection
}

void physModel::SetContent(physMesh* mesh) {
	content = mesh;
	if (content != 0) {
		physvec3 min = mesh->vertices[0];
		physvec3 max = mesh->vertices[0];

		for (int i = 1; i < mesh->numTriangles * 3; ++i) {
			min.x = fminf(mesh->vertices[i].x, min.x);
			min.y = fminf(mesh->vertices[i].y, min.y);
			min.z = fminf(mesh->vertices[i].z, min.z);

			max.x = fmaxf(mesh->vertices[i].x, max.x);
			max.y = fmaxf(mesh->vertices[i].y, max.y);
			max.z = fmaxf(mesh->vertices[i].z, max.z);
		}
		bounds = FromMinMax(min, max);
	}
}

physmat4 GetWorldMatrix(const physModel& model) {
	physmat4 translation = Translation(model.position);
	physmat4 rotation = Rotation(model.rotation.x, model.rotation.y, model.rotation.z);
	physmat4 localMat = /* Scale * */ rotation * translation;

	physmat4 parentMat;
	if (model.parent != 0) {
		parentMat = GetWorldMatrix(*model.parent);
	}

	return localMat * parentMat;
}

OBB GetOBB(const physModel& model) {
	physmat4 world = GetWorldMatrix(model);
	physAABB aabb = model.GetBounds();
	OBB obb;

	obb.size = aabb.size;
	obb.position = MultiplyPoint(aabb.position, world);
	obb.orientation = Cut(world, 3, 3);

	return obb;
}

float ModelRay(const physModel& model, const physRay& ray) {
	physmat4 world = GetWorldMatrix(model);
	physmat4 inv = Inverse(world);
	physRay local;
	local.origin = MultiplyPoint(ray.origin, inv);
	local.direction = MultiplyVector(ray.direction, inv);
	local.NormalizeDirection();
	if (model.GetMesh() != 0) {
		return MeshRay(*(model.GetMesh()), local);
	}
	return -1;
}

bool Linetest(const physModel& model, const Line& line) {
	physmat4 world = GetWorldMatrix(model);
	physmat4 inv = Inverse(world);
	Line local;
	local.start = MultiplyPoint(line.start, inv);
	local.end = MultiplyPoint(line.end, inv);
	if (model.GetMesh() != 0) {
		return Linetest(*(model.GetMesh()), local);
	}
	return false;
}

bool ModelSphere(const physModel& model, const Sphere& sphere) {
	physmat4 world = GetWorldMatrix(model);
	physmat4 inv = Inverse(world);
	Sphere local;
	local.position = MultiplyPoint(sphere.position, inv);
	if (model.GetMesh() != 0) {
		return MeshSphere(*(model.GetMesh()), local);
	}
	return false;
}

bool ModelAABB(const physModel& model, const physAABB& aabb) {
	physmat4 world = GetWorldMatrix(model);
	physmat4 inv = Inverse(world);
	OBB local;
	local.size = aabb.size;
	local.position = MultiplyPoint(aabb.position, inv);
	local.orientation = Cut(inv, 3, 3);
	if (model.GetMesh() != 0) {
		return MeshOBB(*(model.GetMesh()), local);
	}
	return false;
}

bool ModelOBB(const physModel& model, const OBB& obb) {
	physmat4 world = GetWorldMatrix(model);
	physmat4 inv = Inverse(world);
	OBB local;
	local.size = obb.size;
	local.position = MultiplyPoint(obb.position, inv);
	local.orientation = obb.orientation * Cut(inv, 3, 3);
	if (model.GetMesh() != 0) {
		return MeshOBB(*(model.GetMesh()), local);
	}
	return false;
}

bool ModelPlane(const physModel& model, const Plane& plane) {
	physmat4 world = GetWorldMatrix(model);
	physmat4 inv = Inverse(world);
	Plane local;
	local.normal = MultiplyVector(plane.normal, inv);
	local.distance = plane.distance;
	if (model.GetMesh() != 0) {
		return MeshPlane(*(model.GetMesh()), local);
	}
	return false;
}

bool ModelTriangle(const physModel& model, const Triangle& triangle) {
	physmat4 world = GetWorldMatrix(model);
	physmat4 inv = Inverse(world);
	Triangle local;
	local.a = MultiplyPoint(triangle.a, inv);
	local.b = MultiplyPoint(triangle.b, inv);
	local.c = MultiplyPoint(triangle.c, inv);
	if (model.GetMesh() != 0) {
		return MeshTriangle(*(model.GetMesh()), local);
	}
	return false;
}

Point Intersection(Plane p1, Plane p2, Plane p3) {
	/*return ((Cross(p2.normal, p3.normal) * -p1.distance) +
	(Cross(p3.normal, p1.normal) * -p2.distance) +
	(Cross(p1.normal, p2.normal) * -p3.distance)) /
	(Dot(p1.normal, Cross(p2.normal, p3.normal)));*/

#if 1
	mat3 D(
		p1.normal.x, p2.normal.x, p3.normal.x,
		p1.normal.y, p2.normal.y, p3.normal.y,
		p1.normal.z, p2.normal.z, p3.normal.z
	);
	physvec3 A(-p1.distance, -p2.distance, -p3.distance);

	mat3 Dx = D, Dy = D, Dz = D;
	Dx._11 = A.x; Dx._12 = A.y; Dx._13 = A.z;
	Dy._21 = A.x; Dy._22 = A.y; Dy._23 = A.z;
	Dz._31 = A.x; Dz._32 = A.y; Dz._33 = A.z;

	float detD = Determinant(D);

	if (CMP(detD, 0)) {
		return Point();
	}

	float detDx = Determinant(Dx);
	float detDy = Determinant(Dy);
	float detDz = Determinant(Dz);

	return Point(detDx / detD, detDy / detD, detDz / detD);
#else 
	vec3 m1(p1.normal.x, p2.normal.x, p3.normal.x);
	vec3 m2(p1.normal.y, p2.normal.y, p3.normal.y);
	vec3 m3(p1.normal.z, p2.normal.z, p3.normal.z);
	vec3 d(-p1.distance, -p2.distance, -p3.distance);

	vec3 u = Cross(m2, m3);
	vec3 v = Cross(m1, d);
	float denom = Dot(m1, u);

	if (CMP(denom, 0.0f)) {
		return Point();
	}

	Point result;
	result.x = Dot(d, u) / denom;
	result.y = Dot(m3, v) / denom;
	result.z = -Dot(m2, v) / denom;
	return result;
#endif
}

void GetCorners(const Frustum& f, physvec3* outCorners) {
	outCorners[0] = Intersection(f._near, f.top, f.left);
	outCorners[1] = Intersection(f._near, f.top, f.right);
	outCorners[2] = Intersection(f._near, f.bottom, f.left);
	outCorners[3] = Intersection(f._near, f.bottom, f.right);
	outCorners[4] = Intersection(f._far, f.top, f.left);
	outCorners[5] = Intersection(f._far, f.top, f.right);
	outCorners[6] = Intersection(f._far, f.bottom, f.left);
	outCorners[7] = Intersection(f._far, f.bottom, f.right);
}

bool Intersects(const Frustum& f, const Point& p) {
	for (int i = 0; i < 6; ++i) {
		physvec3 normal = f.planes[i].normal;
		float dist = f.planes[i].distance;
		float side = Dot(p, normal) + dist;
		if (side < 0.0f) {
			return false;
		}
	}

	return true;
}

bool Intersects(const Frustum& f, const Sphere& s) {
	for (int i = 0; i < 6; ++i) {
		physvec3 normal = f.planes[i].normal;
		float dist = f.planes[i].distance;
		float side = Dot(s.position, normal) + dist;
		if (side < -s.radius) {
			return false;
		}
	}

	return true;
}

float Classify(const physAABB& aabb, const Plane& plane) {
	// maximum extent in direction of plane normal 
	float r = fabsf(aabb.size.x * plane.normal.x)
		+ fabsf(aabb.size.y * plane.normal.y)
		+ fabsf(aabb.size.z * plane.normal.z);

	// signed distance between box center and plane
	//float d = plane.Test(mCenter);
	float d = Dot(plane.normal, aabb.position) + plane.distance;

	// return signed distance
	if (fabsf(d) < r) {
		return 0.0f;
	}
	else if (d < 0.0f) {
		return d + r;
	}
	return d - r;
}

float Classify(const OBB& obb, const Plane& plane) {
	physvec3 normal = MultiplyVector(plane.normal, obb.orientation);

	// maximum extent in direction of plane normal 
	float r = fabsf(obb.size.x * normal.x)
		+ fabsf(obb.size.y * normal.y)
		+ fabsf(obb.size.z * normal.z);

	// signed distance between box center and plane
	//float d = plane.Test(mCenter);
	float d = Dot(plane.normal, obb.position) + plane.distance;

	// return signed distance
	if (fabsf(d) < r) {
		return 0.0f;
	}
	else if (d < 0.0f) {
		return d + r;
	}
	return d - r;
}

bool Intersects(const Frustum& f, const OBB& obb) {
	for (int i = 0; i < 6; ++i) {
		float side = Classify(obb, f.planes[i]);
		if (side < 0) {
			return false;
		}
	}
	return true;
}

bool Intersects(const Frustum& f, const physAABB& aabb) {
	for (int i = 0; i < 6; ++i) {
		float side = Classify(aabb, f.planes[i]);
		if (side < 0) {
			return false;
		}
	}
	return true;
}

physvec3 Unproject(const physvec3& viewportPoint, const physvec2& viewportOrigin, const physvec2& viewportSize, const physmat4& view, const physmat4& projection) {
	// Step 1, Normalize the input vector to the view port
	float normalized[4] = {
		(viewportPoint.x - viewportOrigin.x) / viewportSize.x,
		(viewportPoint.y - viewportOrigin.y) / viewportSize.y,
		viewportPoint.z,
		1.0f
	};

	// Step 2, Translate into NDC space
	float ndcSpace[4] = {
		normalized[0], normalized[1],
		normalized[2], normalized[3]
	};
	// X Range: -1 to 1
	ndcSpace[0] = ndcSpace[0] * 2.0f - 1.0f;
	// Y Range: -1 to 1, our Y axis is flipped!
	ndcSpace[1] = 1.0f - ndcSpace[1] * 2.0f;
	// Z Range: 0 to 1
	if (ndcSpace[2] < 0.0f) {
		ndcSpace[2] = 0.0f;
	}
	if (ndcSpace[2] > 1.0f) {
		ndcSpace[2] = 1.0f;
	}

	// Step 3, NDC to Eye Space
	physmat4 invProjection = Inverse(projection);
	float eyeSpace[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	// eyeSpace = MultiplyPoint(ndcSpace, invProjection);
	Multiply(eyeSpace, ndcSpace, 1, 4, invProjection.asArray, 4, 4);

	// Step 4, Eye Space to World Space
	physmat4 invView = Inverse(view);
	float worldSpace[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	// worldSpace = MultiplyPoint(eyeSpace, invView);
	Multiply(worldSpace, eyeSpace, 1, 4, invView.asArray, 4, 4);

	// Step 5, Undo perspective divide!
	if (!CMP(worldSpace[3], 0.0f)) {
		worldSpace[0] /= worldSpace[3];
		worldSpace[1] /= worldSpace[3];
		worldSpace[2] /= worldSpace[3];
	}

	// Return the resulting world space point
	return physvec3(worldSpace[0], worldSpace[1], worldSpace[2]);
}

physRay GetPickRay(const physvec2& viewportPoint, const physvec2& viewportOrigin, const physvec2& viewportSize, const physmat4& view, const physmat4& projection) {
	physvec3 nearPoint(viewportPoint.x, viewportPoint.y, 0.0f);
	physvec3 farPoint(viewportPoint.x, viewportPoint.y, 1.0f);

	physvec3 pNear = Unproject(nearPoint, viewportOrigin, viewportSize, view, projection);
	physvec3 pFar = Unproject(farPoint, viewportOrigin, viewportSize, view, projection);

	physvec3 normal = Normalized(pFar - pNear);
	physvec3 origin = pNear;

	return physRay(origin, normal);
}

// Chapter 15

void ResetCollisionManifold(CollisionManifold* result) {
	if (result != 0) {
		result->colliding = false;
		result->normal = physvec3(0, 0, 1);
		result->depth = FLT_MAX;
		if (result->contacts.size() > 0) {
			result->contacts.clear();
		}
	}
}

std::vector<Point> GetVertices(const OBB& obb) {
	std::vector<physvec3> v;
	v.resize(8);

	physvec3 C = obb.position;	// OBB Center
	physvec3 E = obb.size;		// OBB Extents
	const float* o = obb.orientation.asArray;
	physvec3 A[] = {			// OBB Axis
		physvec3(o[0], o[1], o[2]),
		physvec3(o[3], o[4], o[5]),
		physvec3(o[6], o[7], o[8]),
	};

	v[0] = C + A[0] * E[0] + A[1] * E[1] + A[2] * E[2];
	v[1] = C - A[0] * E[0] + A[1] * E[1] + A[2] * E[2];
	v[2] = C + A[0] * E[0] - A[1] * E[1] + A[2] * E[2];
	v[3] = C + A[0] * E[0] + A[1] * E[1] - A[2] * E[2];
	v[4] = C - A[0] * E[0] - A[1] * E[1] - A[2] * E[2];
	v[5] = C + A[0] * E[0] - A[1] * E[1] - A[2] * E[2];
	v[6] = C - A[0] * E[0] + A[1] * E[1] - A[2] * E[2];
	v[7] = C - A[0] * E[0] - A[1] * E[1] + A[2] * E[2];

	return v;
}

std::vector<Line> GetEdges(const OBB& obb) {
	std::vector<Line> result;
	result.reserve(12);
	std::vector<Point> v = GetVertices(obb);

	int index[][2] = { // Indices of edges
		{ 6, 1 },{ 6, 3 },{ 6, 4 },{ 2, 7 },{ 2, 5 },{ 2, 0 },
		{ 0, 1 },{ 0, 3 },{ 7, 1 },{ 7, 4 },{ 4, 5 },{ 5, 3 }
	};

	for (int j = 0; j < 12; ++j) {
		result.push_back(Line(
			v[index[j][0]], v[index[j][1]]
		));
	}

	return result;
}

std::vector<Plane> GetPlanes(const OBB& obb) {
	physvec3 c = obb.position;	// OBB Center
	physvec3 e = obb.size;		// OBB Extents
	const float* o = obb.orientation.asArray;
	physvec3 a[] = {			// OBB Axis
		physvec3(o[0], o[1], o[2]),
		physvec3(o[3], o[4], o[5]),
		physvec3(o[6], o[7], o[8]),
	};

	std::vector<Plane> result;
	result.resize(6);

	result[0] = Plane(a[0], Dot(a[0], (c + a[0] * e.x)));
	result[1] = Plane(a[0] * -1.0f, -Dot(a[0], (c - a[0] * e.x)));
	result[2] = Plane(a[1], Dot(a[1], (c + a[1] * e.y)));
	result[3] = Plane(a[1] * -1.0f, -Dot(a[1], (c - a[1] * e.y)));
	result[4] = Plane(a[2], Dot(a[2], (c + a[2] * e.z)));
	result[5] = Plane(a[2] * -1.0f, -Dot(a[2], (c - a[2] * e.z)));

	return result;
}


bool ClipToPlane(const Plane& plane, const Line& line, Point* outPoint) {
	physvec3 ab = line.end - line.start;

	float nA = Dot(plane.normal, line.start);
	float nAB = Dot(plane.normal, ab);

	if (CMP(nAB, 0)) {
		return false;
	}

	float t = (plane.distance - nA) / nAB;
	if (t >= 0.0f && t <= 1.0f) {
		if (outPoint != 0) {
			*outPoint = line.start + ab * t;
		}
		return true;
	}

	return false;
}

std::vector<Point> ClipEdgesToOBB(const std::vector<Line>& edges, const OBB& obb) {
	std::vector<Point> result;
	result.reserve(edges.size() * 3);
	Point intersection;

	std::vector<Plane>& planes = GetPlanes(obb);

	for (int i = 0; i < (int) planes.size(); ++i) {
		for (int j = 0; j < (int) edges.size(); ++j) {
			if (ClipToPlane(planes[i], edges[j], &intersection)) {
				if (PointInOBB(intersection, obb)) {
					result.push_back(intersection);
				}
			}
		}
	}

	return result;
}

float PenetrationDepth(const OBB& o1, const OBB& o2, const physvec3& axis, bool* outShouldFlip) {
	Interval i1 = GetInterval(o1, Normalized(axis));
	Interval i2 = GetInterval(o2, Normalized(axis));

	if (!((i2.min <= i1.max) && (i1.min <= i2.max))) {
		return 0.0f; // No penerattion
	}

	float len1 = i1.max - i1.min;
	float len2 = i2.max - i2.min;
	float min = fminf(i1.min, i2.min);
	float max = fmaxf(i1.max, i2.max);
	float length = max - min;

	if (outShouldFlip != 0) {
		*outShouldFlip = (i2.min < i1.min);
	}

	return (len1 + len2) - length;
}

CollisionManifold FindCollisionFeatures(const OBB& A, const OBB& B) {
	CollisionManifold result; // Will return result of intersection!
	ResetCollisionManifold(&result);

	Sphere s1(A.position, Magnitude(A.size));
	Sphere s2(B.position, Magnitude(B.size));

	if (!SphereSphere(s1, s2)) {
		return result;
	}

	const float* o1 = A.orientation.asArray;
	const float* o2 = B.orientation.asArray;

	physvec3 test[15] = {
		physvec3(o1[0], o1[1], o1[2]),
		physvec3(o1[3], o1[4], o1[5]),
		physvec3(o1[6], o1[7], o1[8]),
		physvec3(o2[0], o2[1], o2[2]),
		physvec3(o2[3], o2[4], o2[5]),
		physvec3(o2[6], o2[7], o2[8])
	};

	for (int i = 0; i < 3; ++i) { // Fill out rest of axis
		test[6 + i * 3 + 0] = Cross(test[i], test[0]);
		test[6 + i * 3 + 1] = Cross(test[i], test[1]);
		test[6 + i * 3 + 2] = Cross(test[i], test[2]);
	}

	physvec3* hitNormal = 0;
	bool shouldFlip;

	for (int i = 0; i < 15; ++i) {
		if (test[i].x < 0.000001f) test[i].x = 0.0f;
		if (test[i].y < 0.000001f) test[i].y = 0.0f;
		if (test[i].z < 0.000001f) test[i].z = 0.0f;
		if (MagnitudeSq(test[i])< 0.001f) {
			continue;
		}

		float depth = PenetrationDepth(A, B, test[i], &shouldFlip);
		if (depth <= 0.0f) {
			return result;
		}
		else if (depth < result.depth) {
			if (shouldFlip) {
				test[i] = test[i] * -1.0f;
			}
			result.depth = depth;
			hitNormal = &test[i];
		}
	}

	if (hitNormal == 0) {
		return result;
	}
	physvec3 axis = Normalized(*hitNormal);

	std::vector<Point> c1 = ClipEdgesToOBB(GetEdges(B), A);
	std::vector<Point> c2 = ClipEdgesToOBB(GetEdges(A), B);
	result.contacts.reserve(c1.size() + c2.size());
	result.contacts.insert(result.contacts.end(), c1.begin(), c1.end());
	result.contacts.insert(result.contacts.end(), c2.begin(), c2.end());

	Interval i = GetInterval(A, axis);
	float distance = (i.max - i.min)* 0.5f - result.depth * 0.5f;
	physvec3 pointOnPlane = A.position + axis * distance;

	for (int i = result.contacts.size() - 1; i >= 0; --i) {
		physvec3 contact = result.contacts[i];
		result.contacts[i] = contact + (axis * Dot(axis, pointOnPlane - contact));

		// This bit is in the "There is more" section of the book
		for (int j = result.contacts.size() - 1; j > i; --j) {
			if (MagnitudeSq(result.contacts[j] - result.contacts[i]) < 0.0001f) {
				result.contacts.erase(result.contacts.begin() + j);
				break;
			}
		}
	}

	result.colliding = true;
	result.normal = axis;

	return result;
}

CollisionManifold FindCollisionFeatures(const Sphere& A, const Sphere& B) {
	CollisionManifold result; // Will return result of intersection!
	ResetCollisionManifold(&result);

	float r = A.radius + B.radius;
	physvec3 d = B.position - A.position;

	if (MagnitudeSq(d) - r * r > 0 || MagnitudeSq(d) == 0.0f) {
		return result;
	}
	Normalize(d);

	result.colliding = true;
	result.normal = d;
	result.depth = fabsf(Magnitude(d) - r) * 0.5f;

	// dtp - Distance to intersection point
	float dtp = A.radius - result.depth;
	Point contact = A.position + d * dtp;

	result.contacts.push_back(contact);

	return result;
}

CollisionManifold FindCollisionFeatures(const OBB& A, const Sphere& B) {
	CollisionManifold result; // Will return result of intersection!
	ResetCollisionManifold(&result);

	Point closestPoint = ClosestPoint(A, B.position);

	float distanceSq = MagnitudeSq(closestPoint - B.position);
	if (distanceSq > B.radius * B.radius) {
		return result;
	}

	physvec3 normal;
	if (CMP(distanceSq, 0.0f)) {
		if (CMP(MagnitudeSq(closestPoint - A.position), 0.0f)) {
			return result;

		}
		// Closest point is at the center of the sphere
		normal = Normalized(closestPoint - A.position);
	}
	else {
		normal = Normalized(B.position - closestPoint);
	}

	Point outsidePoint = B.position - normal * B.radius;

	float distance = Magnitude(closestPoint - outsidePoint);

	result.colliding = true;
	result.contacts.push_back(closestPoint + (outsidePoint - closestPoint) * 0.5f);
	result.normal = normal;
	result.depth = distance * 0.5f;

	return result;
}
