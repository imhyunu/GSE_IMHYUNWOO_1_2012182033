typedef struct CollisionBox {
	float left, right, top, bottom;
	CollisionBox() {}
	CollisionBox(float l, float r, float t, float b) : left(l), right(r), top(t), bottom(b) {}
} CollBox;