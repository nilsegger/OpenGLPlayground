#include "WorldBodyBuilder.hpp"


b2BodyDef WorldBodyBuilder::createBodyDef(b2BodyType type, b2Vec2 position, void * userData)
{
	b2BodyDef bodyDef;
	bodyDef.type = type;
	setBodyDefPosition(bodyDef, position);
	bodyDef.position = position;
	bodyDef.userData = userData;
	return bodyDef;
}

b2BodyDef WorldBodyBuilder::createBodyDef(bool isBullet, b2BodyType type, b2Vec2 position, void * userData)
{
	b2BodyDef bodyDef = createBodyDef(type, position, userData);
	bodyDef.bullet = isBullet;
	return bodyDef;
}

void WorldBodyBuilder::setBodyDefPosition(b2BodyDef & bodyDef, b2Vec2 position)
{
	bodyDef.position.Set(position.x, position.y);
}

b2FixtureDef WorldBodyBuilder::createFixtureDef(float density, float friction, float restitution, bool isSensor)
{
	b2FixtureDef fixtureDef;
	fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.restitution = restitution;
	fixtureDef.isSensor = isSensor;

	return fixtureDef;
}

b2FixtureDef WorldBodyBuilder::createFixtureDef(b2Shape * shape, float density, float friction, float restitution)
{
	b2FixtureDef fixtureDef = WorldBodyBuilder::createFixtureDef(density, friction, restitution);
	fixtureDef.shape = shape;
	return fixtureDef;
}

b2FixtureDef WorldBodyBuilder::createFixtureDef(b2Shape * shape, bool isSensor, float density, float friction, float restitution)
{
	b2FixtureDef fixtureDef = WorldBodyBuilder::createFixtureDef(density, friction, restitution, isSensor);
	fixtureDef.shape = shape;
	return fixtureDef;
}

b2PolygonShape WorldBodyBuilder::createPolygonShape(b2Vec2 * vertices, int fontSize)
{
	b2PolygonShape shape;
	shape.Set(vertices, fontSize);
	return shape;
}

b2PolygonShape WorldBodyBuilder::createPolygonShape(std::vector<b2Vec2> vertices)
{
	int fontSize = int(vertices.size());
	if (fontSize > MAX_VERTICES) {
		std::cout << "Shape Builder only allows a max of " << MAX_VERTICES << " vertices." << __LINE__ - 4 << std::endl;
		return b2PolygonShape();
	}
	b2Vec2 verticesArr[MAX_VERTICES];
	for (int i = 0; i < fontSize; i++) verticesArr[i] = vertices[i];
	return createPolygonShape(verticesArr, fontSize);
}

b2EdgeShape WorldBodyBuilder::createEdgeShape(b2Vec2 start, b2Vec2 end)
{
	b2EdgeShape edgeShape;
	edgeShape.Set(start, end);
	return edgeShape;
}

b2CircleShape WorldBodyBuilder::createCircleShape(b2Vec2 localPosition, float32 radius)
{
	b2CircleShape circleShape;
	circleShape.m_p = localPosition;
	circleShape.m_radius = radius;
	return circleShape;
}


b2Body * WorldBodyBuilder::instantiateBody(b2BodyDef & bodyDef, b2World * world)
{
	if (world->IsLocked()) {
		std::cout << "Can't instantiateBody because world is locked" << std::endl;
		return nullptr;
	}
	return world->CreateBody(&bodyDef);
}

b2Fixture * WorldBodyBuilder::instantiateFixture(b2FixtureDef & fixtureDef, b2Body * body)
{
	return body->CreateFixture(&fixtureDef);
}

b2Joint * WorldBodyBuilder::Joints::instantiateJoint(b2JointDef * jointDef, b2World * world)
{
	return world->CreateJoint(jointDef);
}

b2DistanceJointDef WorldBodyBuilder::Joints::createDistanceJointDef(b2Body * bodyA, b2Vec2 localAnchorA, b2Body * bodyB, b2Vec2 localAnchorB, bool collideConnected, void * userData)
{
	b2DistanceJointDef jointDef;
	jointDef.Initialize(bodyA, bodyB, bodyA->GetPosition() + localAnchorA, bodyB->GetPosition() + localAnchorB);
	jointDef.collideConnected = collideConnected;
	jointDef.userData = userData;
	return jointDef;
}

b2RevoluteJointDef WorldBodyBuilder::Joints::createRevoluteJointDef(b2Body * bodyA, b2Vec2 localAnchorA, b2Body * bodyB, bool collideConnected, void * userData)
{
	b2RevoluteJointDef jointDef;
	jointDef.Initialize(bodyA, bodyB, bodyA->GetPosition() + localAnchorA);
	jointDef.collideConnected = collideConnected;
	jointDef.userData = userData;
	return jointDef;
}

b2RevoluteJointDef WorldBodyBuilder::Joints::createRevoluteJointDef(b2Body * bodyA, b2Vec2 localAnchorA, b2Body * bodyB, float32 upperAngle, float32 lowerAngle, bool collideConnected, void * userData)
{
	b2RevoluteJointDef jointDef = createRevoluteJointDef(bodyA, localAnchorA, bodyB, collideConnected, userData);
	jointDef.enableLimit = true;
	jointDef.lowerAngle = lowerAngle;
	jointDef.upperAngle = upperAngle;
	return jointDef;
}

b2RevoluteJointDef WorldBodyBuilder::Joints::createRevoluteJointDefMotor(b2Body * bodyA, b2Vec2 localAnchorA, b2Body * bodyB, float32 motorSpeed, float32 maxMotorSpeed, bool collideConnected, void * userData)
{
	b2RevoluteJointDef jointDef = createRevoluteJointDef(bodyA, localAnchorA, bodyB, collideConnected, userData);

	jointDef.enableMotor = true;
	jointDef.motorSpeed = motorSpeed;
	jointDef.maxMotorTorque = maxMotorSpeed;

	return jointDef;
}

b2WheelJointDef WorldBodyBuilder::Joints::createWheelJointDef(b2Body * bodyA, b2Vec2 localAnchorA, b2Body * bodyB, b2Vec2 localAnchorB, bool collideConnected, void * userData)
{
	b2WheelJointDef wheelJoint;
	wheelJoint.bodyA = bodyA;
	wheelJoint.bodyB = bodyB;
	wheelJoint.localAnchorA = localAnchorA;
	wheelJoint.localAnchorB = localAnchorA;
	wheelJoint.collideConnected = false;
	return wheelJoint;
}

b2WheelJointDef WorldBodyBuilder::Joints::createWheelJointDef(b2Body * bodyA, b2Vec2 localAnchorA, b2Body * bodyB, b2Vec2 localAnchorB, float32 motorSpeed, float32 maxMotorspeed, bool collideConnected, void * userData)
{
	b2WheelJointDef wheelDef = createWheelJointDef(bodyA, localAnchorA, bodyB, localAnchorB, collideConnected, userData);
	wheelDef.enableMotor = true;
	wheelDef.motorSpeed = motorSpeed;
	wheelDef.maxMotorTorque = maxMotorspeed;
	return wheelDef;
}

b2PrismaticJointDef WorldBodyBuilder::Joints::createPrismaticJointDef(b2Body * bodyA, b2Vec2 worldAnchor, b2Body * bodyB, b2Vec2 worldAxis)
{
	b2PrismaticJointDef jointDef;
	jointDef.Initialize(bodyA, bodyB, worldAnchor, worldAxis);
	return jointDef;
}