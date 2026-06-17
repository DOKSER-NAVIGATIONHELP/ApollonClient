#pragma once
#define PI (3.1415927f)

#include <math.h>

static constexpr float DEG_RAD2 = PI / 360.0f;
static constexpr float DEG_RAD = 180.0f / PI;
static constexpr float RAD_DEG = PI / 180.f;

const float HITBOX_HEIGHT = 1.8f;
const float HITBOX_WIDTH_HALF = 0.3f;

inline float lerp(float a, float b, float t) {
	return a + t * (b - a);
}

const struct vec2_t {
	struct {
		float x, y;
	};
	float floatArr[2];
	vec2_t() { x = y = 0; }
	vec2_t(float a, float b) : x(a), y(b) {}
	vec2_t(int a, int b) : x((float)a), y((float)b) {}
	vec2_t &operator=(const vec2_t &copy) {
		x = copy.x;
		y = copy.y;
		return *this;
	}

	static vec2_t fromAngle(float angle){
		return vec2_t((float)-sin(angle), (float)cos(angle));
	}

	bool operator==(const vec2_t &o) const { return x == o.x && y == o.y; }
	bool operator!=(const vec2_t &o) const { return x != o.x || y != o.y; }

	vec2_t sub(float f) {
		return vec2_t(x - f, y - f);
	}
	vec2_t sub(float ox, float oy) {
		return vec2_t(x - ox, y - oy);
	}
	vec2_t div(float f) {
		return vec2_t(x / f, y / f);
	}

	vec2_t div(const vec2_t &o) {
		return vec2_t(x / o.x, y / o.y);
	}
	vec2_t mul(const vec2_t &o) {
		return vec2_t(x * o.x, y * o.y);
	}
	vec2_t mul(float f) {
		return vec2_t(x * f, y * f);
	}
	vec2_t sub(const vec2_t &o) {
		return vec2_t(x - o.x, y - o.y);
	}
	vec2_t add(const vec2_t &o) {
		return vec2_t(x + o.x, y + o.y);
	}
	vec2_t add(float o) {
		return vec2_t(x + o, y + o);
	}
	vec2_t add(float ox, float oy) {
		return vec2_t(x + ox, y + oy);
	}

	vec2_t normalized() {
		return div(magnitude());
	}

	vec2_t cross(){
		return vec2_t(-y, x);
	}

	float dot(float ox, float oy) const { return x * ox + y * oy; }

	float dot(const vec2_t &o) const { return x * o.x + y * o.y; }

	vec2_t normAngles() {
		float x = this->x;
		float y = this->y;
		while (x > 90.f)
			x -= 180.0f;
		while (x < -90.f)
			x += 180.0f;

		while (y > 180.0f)
			y -= 360.0f;
		while (y < -180.0f)
			y += 360.0f;
		return vec2_t(x, y);
	}

	float squaredlen() const { return x * x + y * y; }
	float magnitude() const { return sqrtf(squaredlen()); }
};

const struct vec3_t {
	struct {
		float x, y, z;
	};
	float floatArr[3];

	vec3_t() { x = y = z = 0; }
	vec3_t(int a, int b, int c) : x((float)a), y((float)b), z((float)c) {}
	vec3_t(double a, double b, double c) : x((float)a), y((float)b), z((float)c) {}
	vec3_t(float a, float b, float c) : x(a), y(b), z(c) {}
	vec3_t(float a, float b) : x(a), y(b), z(0) {}
	vec3_t(const vec2_t &copy, float zP) {
		x = copy.x;
		y = copy.y;
		z = zP;
	}
	vec3_t(const vec3_t &copy) {
		x = copy.x;
		y = copy.y;
		z = copy.z;
	}

	vec3_t &operator=(const vec3_t &copy) {
		x = copy.x;
		y = copy.y;
		z = copy.z;

		return *this;
	}

	vec3_t(float *v) : x(v[0]), y(v[1]), z(v[2]) {}

	bool iszero() const { return x == 0 && y == 0 && z == 0; }

	inline bool operator==(const vec3_t &o) const { return x == o.x && y == o.y && z == o.z; };
	bool operator!=(const vec3_t &o) const { return x != o.x || y != o.y || z != o.z; };
	vec3_t operator-() const { return vec3_t(-x, -y, -z); };

	vec3_t mul(const vec3_t &o) const {
		return vec3_t(x * o.x, y * o.y, z * o.z);
	};
	vec3_t mul(float f) const {
		return vec3_t(x * f, y * f, z * f);
	};
	vec3_t mul(float x1, float y1, float z1) const {
		return vec3_t(x * x1, y * y1, z * z1);
	};
	vec3_t div(float f) const {
		return vec3_t(x / f, y / f, z / f);
	};
	vec3_t div(float x1, float y1, float z1) const {
		return vec3_t(x / x1, y / y1, z / z1);
	};
	vec3_t div(const vec3_t &o) const {
		return vec3_t(x / o.x, y / o.y, z / o.z);
	};
	vec3_t add(float f) const {
		return vec3_t(x + f, y + f, z + f);
	};
	vec3_t add(float x1, float y1, float z1) const {
		return vec3_t(x + x1, y + y1, z + z1);
	};
	vec3_t sub(float f) const {
		return vec3_t(x - f, y - f, z - f);
	};

	vec3_t sub(float x1, float y1, float z1) const {
		return vec3_t(x - x1, y - y1, z - z1);
	};

	vec3_t floor() const {
		return vec3_t(floorf(x), floorf(y), floorf(z));
	};

	vec3_t add(const vec3_t &o) const {
		return vec3_t(x + o.x, y + o.y, z + o.z);
	}
	vec3_t sub(const vec3_t &o) const {
		return vec3_t(x - o.x, y - o.y, z - o.z);
	}

	float squaredlen() const { return x * x + y * y + z * z; }
	float squaredxzlen() const { return x * x + z * z; }

	vec3_t lerp(const vec3_t& other, float tx, float ty, float tz) const {
		vec3_t ne;
		ne.x = x + tx * (other.x - x);
		ne.y = y + ty * (other.y - y);
		ne.z = z + tz * (other.z - z);
		return ne;
	}

	vec3_t lerp(const vec3_t other, float val) const {
		vec3_t ne;
		ne.x = x + val * (other.x - x);
		ne.y = y + val * (other.y - y);
		ne.z = z + val * (other.z - z);
		return ne;
	}

	vec3_t lerp(const vec3_t *other, float val) const {
		vec3_t ne;
		ne.x = x + val * (other->x - x);
		ne.y = y + val * (other->y - y);
		ne.z = z + val * (other->z - z);
		return ne;
	}

	vec2_t flatten() const {
		return vec2_t(x, y);
	}

	float sqrxy() const { return x * x + y * y; }

	float dot(const vec3_t &o) const { return x * o.x + y * o.y + z * o.z; }
	float dotxy(const vec3_t &o) const { return x * o.x + y * o.y; }

	float magnitude() const { return sqrtf(squaredlen()); }

	vec3_t normalize() {
		return div(magnitude());
	}

	float dist(const vec3_t &e) const {
		return sub(e).magnitude();
	}

	float Get2DDist(const vec3_t &e) const {
		float dx = e.x - x, dy = e.y - y;
		return sqrtf(dx * dx + dy * dy);
	}

	float magnitudexy() const { return sqrtf(x * x + y * y); }
	float magnitudexz() const { return sqrtf(x * x + z * z); }

	vec3_t cross(const vec3_t &b) {
		return vec3_t(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
	}
	float cxy(const vec3_t &a) { return x * a.y - y * a.x; }
	
	vec2_t CalcAngle(vec3_t dst) {
		vec3_t diff = dst.sub(*this);

		diff.y = diff.y / diff.magnitude();
		vec2_t angles;
		angles.x = asinf(diff.y) * -DEG_RAD;
		angles.y = (float)-atan2f(diff.x, diff.z) * DEG_RAD;

		return angles;
	}
	
vec2_t CalcMobAngle(vec3_t dst, float hitboxHeight) const {
    float a1 = -hitboxHeight;
    float a5 = 0.0f;
    float a3 = -hitboxHeight / 2.0f;

    float a2 = (a1 + a3) / 2.0f;
    float a4 = (a3 + a5) / 2.0f;

    float hitboxPoints[] = {a1, a2, a3, a4, a5};

    float closestPoint = hitboxPoints[0];
    float minDistance = std::abs(dst.y - (y + hitboxPoints[0]));

    for (int i = 1; i < 5; ++i) {
        float distance = std::abs(dst.y - (y + hitboxPoints[i]));
        if (distance < minDistance) {
            minDistance = distance;
            closestPoint = hitboxPoints[i];
        }
    }

    vec3_t diff = dst.sub(*this);
    diff.y = dst.y - (y + closestPoint);

    diff.y = diff.y / diff.magnitude();

    vec2_t angles;
    angles.x = std::asinf(diff.y) * -DEG_RAD;
    angles.y = (float)-std::atan2f(diff.x, diff.z) * DEG_RAD;

    return angles;
}

	
	vec2_t CalcPlayerAngle(vec3_t dst) const {
        vec3_t diff = dst.sub(*this);

        if (dst.y - 0.6 > y) {
            diff.y = (dst.y - (y + 1));
        }

        diff.y = diff.y / diff.magnitude();
        vec2_t angles;
        angles.x = std::asinf(diff.y) * -DEG_RAD;
        angles.y = (float)-std::atan2f(diff.x, diff.z) * DEG_RAD;

        return angles;
    }
};

const struct vec3_ti {
	struct {
		int x, y, z;
	};
	int intArr[3];
};