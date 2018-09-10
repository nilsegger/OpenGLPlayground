#pragma once

#include <Box2D\Box2D.h>
#include <vector>
#include <iostream>

#include "config.hpp"

class WorldBodyBuilder
{
			//float density, float friction, float restitution
public:
	static b2BodyDef createBodyDef(b2BodyType type = b2_staticBody, b2Vec2 position = { 0,0 }, void * userData = nullptr);
	static b2BodyDef createBodyDef(bool isBullet, b2BodyType type = b2_staticBody, b2Vec2 position = { 0,0 }, void * userData = nullptr);
	static void setBodyDefPosition(b2BodyDef &bodyDef, b2Vec2 position);

	static b2FixtureDef createFixtureDef(float density = 1.f, float friction = 1.f, float restitution = 0.f, bool isSensor = false);
	static b2FixtureDef createFixtureDef(b2Shape * shape, float density = 1.f, float friction = 1.f, float restitution = 0.f);
	static b2FixtureDef createFixtureDef(b2Shape * shape, bool isSensor, float density = 1.f, float friction = 1.f, float restitution = 0.f);

	static b2PolygonShape createPolygonShape(b2Vec2 * vertices, int size);
	static b2PolygonShape createPolygonShape(std::vector<b2Vec2> vertices);

	static b2EdgeShape createEdgeShape(b2Vec2 start, b2Vec2 end);

	static b2CircleShape createCircleShape(b2Vec2 localPosition, float32 radius);

	static b2Body * instantiateBody(b2BodyDef &bodyDef, b2World * world);
	static b2Fixture * instantiateFixture(b2FixtureDef &fixtureDef, b2Body * body);

	//static Shape * instantiateShape(ShapeDefinition shapeDef, b2World * world);

	class Joints {
	public:
		static b2Joint * instantiateJoint(b2JointDef * jointDef, b2World * world);
		static b2DistanceJointDef createDistanceJointDef(b2Body * bodyA, b2Vec2 localAnchorA, b2Body * bodyB, b2Vec2 localAnchorB, bool collideConnected = false, void * userData = nullptr);
		static b2RevoluteJointDef createRevoluteJointDef(b2Body * bodyA, b2Vec2 localAnchorA, b2Body * bodyB, bool collideConnected = false, void * userData = nullptr);
		static b2RevoluteJointDef createRevoluteJointDef(b2Body * bodyA, b2Vec2 localAnchorA, b2Body * bodyB, float32 upperAngle, float32 lowerAngle, bool collideConnected = false, void * userData = nullptr);
		static b2RevoluteJointDef createRevoluteJointDefMotor(b2Body * bodyA, b2Vec2 localAnchorA, b2Body * bodyB, float32 motorSpeed, float32 maxMotorSpeed, bool collideConnected = false, void * userData = nullptr);
		static b2WheelJointDef createWheelJointDef(b2Body * bodyA, b2Vec2 localAnchorA, b2Body * bodyB, b2Vec2 localAnchorB, bool collideConnected = false, void * userData = nullptr);
		static b2WheelJointDef createWheelJointDef(b2Body * bodyA, b2Vec2 localAnchorA, b2Body * bodyB, b2Vec2 localAnchorB, float32 motorSpeed, float32 maxMotorspeed, bool collideConnected = false, void * userData = nullptr);
		static b2PrismaticJointDef createPrismaticJointDef(b2Body * bodyA, b2Vec2 localAnchorA, b2Body * bodyB, b2Vec2 worldAxis);
	};
};


