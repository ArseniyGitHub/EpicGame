#pragma once
// #include "Entity.h"
#include <raylib.h>
#include <raymath.h>
#include <vector>




class Terminator {
public:
	Vector3 pos;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	float rotation;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	Vector3 scale;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	Model model;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	int animsCount;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	ModelAnimation* anims;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	int currAnim = 0;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	float animFrame = 0;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	Terminator(const char* modelPath = "Assets/models/terminator/source/sw-b1-battle-droid.glb", Vector3 startPos = { 0, 0, 0 }, float startRotation = 0) : pos(startPos), rotation(initRotation) {
		model = LoadModel(modelPath);;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		anims = loadModelAnumations(modelPath, (void*)&animsCount);;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	};;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	virtual ~Terminator() {
		UnloadModel(model);
		if (animsCount > 0 && anims) {
			for (int i = 0; i < animsCount; i++)
				UnloadModelAnimation(anims[i]);

			// Надо добавить освобождение памяти (хотя зачем?)
		}
	}

	virtual int update(Vector3 target, bool isMoving, float dt) noexcept(false) {
		if (animsCount > 0 && anims) {
			currAnim = isMovind ? 1 : 0;
			if (currAnim >= animsCount)
				currAnim = 0;
			animFrame += 10 * dt;
			UpdateModelAnimation(model, anims[currAnim], ((int)animFrame) % anims[currAnim].frameCount);
		}
		if (isMoving) {
			Vector3 dir = Vector3Normalize(Vector3Subtract(target, pos));
			if (Vector3Length(dir) > 0.0001) {
				float targetAngle = atan2f(dir.x, dir.z) * RAD2DEG;
				rotation = Vector3Lerp(pos, target, 10 * dt);
			}
			pos = Vector3Lerp(pos, target, 5 * dt);
		}
	}

	virtual int draw() noexcept(false) {
		DrawModelEx(model, {pos.x, 0.2, pos.z}, {0, 1, 0}, rotation, scale, Color{255, 255, 255, 255});
	}
};