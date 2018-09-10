#ifndef _H_GEOMETRY_3D_
#define _H_GEOMETRY_3D_

#include <vector>
#include <utility>
//#include <cfloat>
#include "vectors.h"
#include "matrices.h"
#include <ostream>

typedef physvec3 Point;

/**
* @struct Line
*
* @author Morgan Smolder
*/
typedef struct Line {
	Point start;
	Point end;

	inline Line() {}
	inline Line(const Point& s, const Point& e) :
		start(s), end(e) { }
} Line;

/**
* @struct physRay
*
* @author Morgan Smolder
*/
typedef struct physRay {
	Point origin;
	physvec3 direction;

	inline physRay() : direction(0.0f, 0.0f, 1.0f) {}
	inline physRay(const Point& o, const physvec3& d) :
		origin(o), direction(d) {
		NormalizeDirection();
	}
	inline void NormalizeDirection() {
		Normalize(direction);
	}
} physRay;

/**
* @struct Sphere
*
* @author Morgan Smolder
*/
typedef struct Sphere {
	Point position;
	float radius;

	inline Sphere() : radius(1.0f) { }
	inline Sphere(const Point& p, float r) :
		position(p), radius(r) { }
} Sphere;

/**
* @struct physAABB
*
* @author Morgan Smolder
*/
typedef struct physAABB {
	Point position;
	physvec3 size; // HALF SIZE!

	inline physAABB() : size(1, 1, 1) { }
	inline physAABB(const Point& p, const physvec3& s) :
		position(p), size(s) { }
} physAABB;

/**
* @struct OBB
*
* @author Morgan Smolder
*/
typedef struct OBB {
	Point position;
	physvec3 size; // HALF SIZE!
	mat3 orientation;

	inline OBB() : size(1, 1, 1) { }
	inline OBB(const Point& p, const physvec3& s) :
		position(p), size(s) { }
	inline OBB(const Point& p, const physvec3& s, const mat3& o) :
		position(p), size(s), orientation(o) { }
} OBB;

/**
* @struct Plane
*
* @author Morgan Smolder
*/
typedef struct Plane {
	physvec3 normal;
	float distance;

	inline Plane() : normal(1, 0, 0) { }
	inline Plane(const physvec3& n, float d) :
		normal(n), distance(d) { }
} Plane;

/**
* @struct Triangle
*
* @author Morgan Smolder
*/
typedef struct Triangle {
	union {
		struct {
			Point a;
			Point b;
			Point c;
		};
		struct {
			Point p1;
			Point p2;
			Point p3;
		};

		Point points[3];
		float values[9];
	};

	inline Triangle() { }
	inline Triangle(const Point& _p1, const Point& _p2, const Point& _p3) :
		a(_p1), b(_p2), c(_p3) { }
} Triangle;

/**
* @struct BVHNode
*
* @author Morgan Smolder
*/
typedef struct BVHNode {
	physAABB bounds;
	BVHNode* children;
	int numTriangles;
	int* triangles;

	BVHNode() : children(0), numTriangles(0), triangles(0) {}
} BVHNode;

/**
* @struct physMesh
*
* @author Morgan Smolder
*/
typedef struct physMesh {
	int numTriangles;
	union {
		Triangle* triangles;
		Point* vertices;
		float* values;
	};
	BVHNode* accelerator;

	physMesh() : numTriangles(0), values(0), accelerator(0) {}
} physMesh;

/**
* @class physModel
*
* @author Morgan Smolder
*/
class physModel {
protected:
	physMesh* content;
	physAABB bounds;
public:
	physvec3 position;
	physvec3 rotation;
	bool flag;
	physModel* parent;

	inline physModel() : parent(0), content(0), flag(false) { }
	inline physMesh* GetMesh() const {
		return content;
	}
	inline physAABB GetBounds() const {
		return bounds;
	}

	void SetContent(physMesh* mesh);
};

/**
* @struct Interval
*
* @author Morgan Smolder
*/
typedef struct Interval {
	float min;
	float max;
} Interval;

/**
* @struct Frustum
*
* @author Morgan Smolder
*/
typedef struct Frustum {
	union {
		struct {
			Plane top;
			Plane bottom;
			Plane left;
			Plane right;
			Plane _near;
			Plane _far;
		};
		Plane planes[6];
	};

	inline Frustum() { }
} Frustum;

/**
* @struct RaycastResult
*
* @author Morgan Smolder
*/
typedef struct RaycastResult {
	physvec3 point;
	physvec3 normal;
	float t;
	bool hit;
} RaycastResult;

void ResetRaycastResult(RaycastResult* outResult);

Point Intersection(Plane p1, Plane p2, Plane p3);
void GetCorners(const Frustum& f, physvec3* outCorners);

typedef physvec3 Point3D;
typedef Line Line3D;
typedef physRay Ray3D;
typedef physAABB Rectangle3D;
typedef Interval Interval3D;

std::ostream& operator<<(std::ostream& os, const Line& shape);
std::ostream& operator<<(std::ostream& os, const physRay& shape);
std::ostream& operator<<(std::ostream& os, const Sphere& shape);
std::ostream& operator<<(std::ostream& os, const physAABB& shape);
std::ostream& operator<<(std::ostream& os, const OBB& shape);
std::ostream& operator<<(std::ostream& os, const Plane& shape);
std::ostream& operator<<(std::ostream& os, const Triangle& shape);

float Length(const Line& line);
float LengthSq(const Line& line);
physRay FromPoints(const Point& from, const Point& to);
physvec3 GetMin(const physAABB& aabb);
physvec3 GetMax(const physAABB& aabb);
physAABB FromMinMax(const physvec3& min, const physvec3& max);
float PlaneEquation(const Point& point, const Plane& plane);
float PlaneEquation(const Plane& plane, const Point& point);

bool PointInSphere(const Point& point, const Sphere& sphere);
bool PointInAABB(const Point& point, const physAABB& aabb);
bool PointInOBB(const Point& point, const OBB& obb);
bool PointOnPlane(const Point& point, const Plane& plane);
bool PointOnLine(const Point& point, const Line& line);
bool PointOnRay(const Point& point, const physRay& ray);

bool PointInPlane(const Point& point, const Plane& plane);
bool PointInLine(const Point& point, const Line& line);
bool PointInRay(const Point& point, const physRay& ray);
bool ContainsPoint(const Sphere& sphere, const Point& point);
bool ContainsPoint(const Point& point, const Sphere& sphere);
bool ContainsPoint(const physAABB& aabb, const Point& point);
bool ContainsPoint(const Point& point, const physAABB& aabb);
bool ContainsPoint(const Point& point, const OBB& obb);
bool ContainsPoint(const OBB& obb, const Point& point);
bool ContainsPoint(const Point& point, const Plane& plane);
bool ContainsPoint(const Plane& plane, const Point& point);
bool ContainsPoint(const Point& point, const Line& line);
bool ContainsPoint(const Line& line, const Point& point);
bool ContainsPoint(const Point& point, const physRay& ray);
bool ContainsPoint(const physRay& ray, const Point& point);

Point ClosestPoint(const Sphere& sphere, const Point& point);
Point ClosestPoint(const physAABB& aabb, const Point& point);
Point ClosestPoint(const OBB& obb, const Point& point);
Point ClosestPoint(const Plane& plane, const Point& point);
Point ClosestPoint(const Line& line, const Point& point);
Point ClosestPoint(const physRay& ray, const Point& point);

Point ClosestPoint(const Point& point, const Sphere& sphere);
Point ClosestPoint(const Point& point, const physAABB& aabb);
Point ClosestPoint(const Point& point, const OBB& obb);
Point ClosestPoint(const Point& point, const Plane& plane);
Point ClosestPoint(const Point& point, const Line& line);
Point ClosestPoint(const Point& point, const physRay& ray);
Point ClosestPoint(const Point& p, const Triangle& t);

Interval GetInterval(const physAABB& aabb, const physvec3& axis);
Interval GetInterval(const OBB& obb, const physvec3& axis);
Interval GetInterval(const Triangle& triangle, const physvec3& axis);

bool OverlapOnAxis(const physAABB& aabb, const OBB& obb, const physvec3& axis);
bool OverlapOnAxis(const OBB& obb1, const OBB& obb2, const physvec3& axis);
bool OverlapOnAxis(const physAABB& aabb, const Triangle& triangle, const physvec3& axis);
bool OverlapOnAxis(const OBB& obb, const Triangle& triangle, const physvec3& axis);
bool OverlapOnAxis(const Triangle& t1, const Triangle& t2, const physvec3& axis);

bool SphereSphere(const Sphere& s1, const Sphere& s2);
bool SphereAABB(const Sphere& sphere, const physAABB& aabb);
bool SphereOBB(const Sphere& sphere, const OBB& obb);
bool SpherePlane(const Sphere& sphere, const Plane& plane);
bool AABBAABB(const physAABB& aabb1, const physAABB& aabb2);
bool AABBOBB(const physAABB& aabb, const OBB& obb);
bool AABBPlane(const physAABB& aabb, const Plane& plane);
bool OBBOBB(const OBB& obb1, const OBB& obb2);
bool OBBPlane(const OBB& obb, const Plane& plane);
bool PlanePlane(const Plane& plane1, const Plane& plane2);

#define AABBSphere(aabb, sphere) \
	SphereAABB(Sphere, physAABB)
#define OBBSphere(obb, sphere) \
	SphereOBB(sphere, obb)
#define PlaneSphere(plane, sphere) \
	SpherePlane(sphere, plane)
#define OBBAABB(obb, aabb) \
	AABBOBB(aabb, obb)
#define PlaneAABB(plane, aabb) \
	AABBPlane(aabb, plane)
#define PlaneOBB(plane, obb) \
	OBBPlane(obb, plane)

bool Raycast(const Sphere& sphere, const physRay& ray, RaycastResult* outResult);
bool Raycast(const physAABB& aabb, const physRay& ray, RaycastResult* outResult);
bool Raycast(const OBB& obb, const physRay& ray, RaycastResult* outResult);
bool Raycast(const Plane& plane, const physRay& ray, RaycastResult* outResult);
bool Raycast(const Triangle& triangle, const physRay& ray, RaycastResult* outResult);

bool Linetest(const Sphere& sphere, const Line& line);
bool Linetest(const physAABB& aabb, const Line& line);
bool Linetest(const OBB& obb, const Line& line);
bool Linetest(const Plane& plane, const Line& line);
bool Linetest(const Triangle& triangle, const Line& line);

bool Raycast(const physRay& ray, const Sphere& sphere, RaycastResult* outResult);
bool Raycast(const physRay& ray, const physAABB& aabb, RaycastResult* outResult);
bool Raycast(const physRay& ray, const OBB& obb, RaycastResult* outResult);
bool Raycast(const physRay& ray, const Plane& plane, RaycastResult* outResult);
bool Linetest(const Line& line, const Sphere& sphere);
bool Linetest(const Line& line, const physAABB& aabb);
bool Linetest(const Line& line, const OBB& obb);
bool Linetest(const Line& line, const Plane& plane);

physvec3 BarycentricOptimized(const Point& p, const Triangle& t);
physvec3 Centroid(const Triangle& t);

bool PointInTriangle(const Point& p, const Triangle& t);
Plane FromTriangle(const Triangle& t);
Point ClosestPoint(const Triangle& t, const Point& p);
bool TriangleSphere(const Triangle& t, const Sphere& s);
bool TriangleAABB(const Triangle& t, const physAABB& a);
bool TriangleOBB(const Triangle& t, const OBB& o);
bool TriangleTriangle(const Triangle& t1, const Triangle& t2);
bool TriangleTriangleRobust(const Triangle& t1, const Triangle& t2);
bool TrianglePlane(const Triangle& t, const Plane& p);

#define SphereTriangle(s, t) \
	TriangleSphere(t, s)
#define AABBTriangle(a, t) \
	TriangleAABB(t, a)
#define OBBTriangle(o, t) \
	TriangleOBB(t, o)
#define PlaneTriangle(p, t) \
	TrianglePlane(t, p)

// A - Edge 0, Point 0
// B - Edge 0, Point 1
// C - Edge 1, Point 0
// D - Edge 1, Point 1
physvec3 SatCrossEdge(const physvec3& a, const physvec3& b, const physvec3& c, const physvec3& d);
physvec3 Barycentric(const Point& p, const Triangle& t);

void AccelerateMesh(physMesh& mesh);
void SplitBVHNode(BVHNode* node, const physMesh& model, int depth);
void FreeBVHNode(BVHNode* node);

bool Linetest(const physMesh& mesh, const Line& line);
bool MeshSphere(const physMesh& mesh, const Sphere& sphere);
bool MeshAABB(const physMesh& mesh, const physAABB& aabb);
bool MeshOBB(const physMesh& mesh, const OBB& obb);
bool MeshPlane(const physMesh& mesh, const Plane& plane);
bool MeshTriangle(const physMesh& mesh, const Triangle& triangle);
float MeshRay(const physMesh& mesh, const physRay& ray);
float Raycast(const physMesh& mesh, const physRay& ray);
float Raycast(const physModel& mesh, const physRay& ray);

physmat4 GetWorldMatrix(const physModel& model);
OBB GetOBB(const physModel& model);

float ModelRay(const physModel& model, const physRay& ray);
bool Linetest(const physModel& model, const Line& line);
bool ModelSphere(const physModel& model, const Sphere& sphere);
bool ModelAABB(const physModel& model, const physAABB& aabb);
bool ModelOBB(const physModel& model, const OBB& obb);
bool ModelPlane(const physModel& model, const Plane& plane);
bool ModelTriangle(const physModel& model, const Triangle& triangle);

float Classify(const physAABB& aabb, const Plane& plane);
float Classify(const OBB& obb, const Plane& plane);

bool Intersects(const Frustum& f, const Point& p);
bool Intersects(const Frustum& f, const Sphere& s);
bool Intersects(const Frustum& f, const physAABB& aabb);
bool Intersects(const Frustum& f, const OBB& obb);

physvec3 Unproject(const physvec3& viewportPoint, const physvec2& viewportOrigin, const physvec2& viewportSize, const physmat4& view, const physmat4& projection);
physRay GetPickRay(const physvec2& viewportPoint, const physvec2& viewportOrigin, const physvec2& viewportSize, const physmat4& view, const physmat4& projection);

// Chapter 15

/**
* @struct CollisionManifold
*
* @author Morgan Smolder
*/
typedef struct CollisionManifold {
	bool colliding;
	physvec3 normal;
	float depth;
	std::vector<physvec3> contacts;
} CollisionManifold;

void ResetCollisionManifold(CollisionManifold* result);

std::vector<Point> GetVertices(const OBB& obb);
std::vector<Line> GetEdges(const OBB& obb);
std::vector<Plane> GetPlanes(const OBB& obb);
bool ClipToPlane(const Plane& plane, const Line& line, Point* outPoint);
std::vector<Point> ClipEdgesToOBB(const std::vector<Line>& edges, const OBB& obb);
float PenetrationDepth(const OBB& o1, const OBB& o2, const physvec3& axis, bool* outShouldFlip);

CollisionManifold FindCollisionFeatures(const Sphere& A, const Sphere& B);
CollisionManifold FindCollisionFeatures(const OBB& A, const Sphere& B);
CollisionManifold FindCollisionFeatures(const OBB& A, const OBB& B);

#endif