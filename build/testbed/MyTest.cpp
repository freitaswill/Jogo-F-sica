#include "test.h"
#pragma once

class MyTest : public Test
{
public:
	MyTest() { } //do nothing, no scene yet

	bool firstFrame = true;
	float minX = -6.0f;
	float maxX = 0.0f;
	float minY = 4.0f;
	float maxY = 6.0f;
	float restitution = 0;
	float friction = 0;
	b2Body* m_body1;
	b2Vec2 m_velocity;
	float m_angularVelocity;
	b2PolygonShape m_shape1;
	b2PolygonShape m_shape2;
	b2Vec2 *vec2 = new b2Vec2(0.0, 0.0);
	b2Body* bodyChar;
	b2Vec2 *forceW = new b2Vec2(0, 2000);
	b2Vec2 *forceA = new b2Vec2(-1000, 0);
	b2Vec2 *forceS = new b2Vec2(0, -1000);
	b2Vec2 *forceD = new b2Vec2(1000, 0);
	b2Vec2 *force = new b2Vec2(2000, 0);

	//Ex 1
	void newCircle(float size, float positionX, float positionY, float density, float friction, float restitution, bool dynamic, b2Vec2 force) {
		m_world->SetGravity(b2Vec2(0.0f, -10.0f));
		{
			b2CircleShape shape;
			shape.m_p.SetZero();
			shape.m_radius = size;


			b2BodyDef bd;
			if (dynamic)
				bd.type = b2_dynamicBody;
			else
				bd.type = b2_staticBody;
			bd.position = b2Vec2(positionX, positionY);
			b2Body* body = m_world->CreateBody(&bd);
			body->CreateFixture(&shape, density);
			body->GetFixtureList()->SetFriction(friction);
			body->GetFixtureList()->SetRestitution(restitution);

			body->ApplyForceToCenter(force, false);
		}
	}

	void newBox(float x, float y, float positionX, float positionY, float rotation, float density, float friction, float restitution, bool dynamic) {
		m_world->SetGravity(b2Vec2(0.0f, 0.0f));
		{
			b2PolygonShape shape;
			shape.SetAsBox(1, 1);
			shape.m_radius = 0.1f;

			float minX = -6.0f;
			float maxX = 0.0f;
			float minY = 4.0f;
			float maxY = 6.0f;


			b2BodyDef bd;
			if (dynamic)
				bd.type = b2_dynamicBody;
			else
				bd.type = b2_staticBody;
			bd.position = b2Vec2(positionX, positionY);
			b2Body* body = m_world->CreateBody(&bd);
			body->CreateFixture(&shape, density);
			body->GetFixtureList()->SetFriction(friction);
			body->GetFixtureList()->SetRestitution(restitution);

		}
	}

	//Ex 8
	void newDuck(float positionX, float positionY, float rotation, float density, float friction, float restitution, bool dynamic) {
		m_world->SetGravity(b2Vec2(0.0f, 0.0f));
		{
			b2BodyDef bd;
			b2CircleShape circle;
			circle.m_p.SetZero();
			circle.m_radius = 0.5;

			bd.type = b2_dynamicBody;
			bd.position.Set(0.0f, 40.0f);
			bd.angle = 0.25f * b2_pi;
			m_body1 = m_world->CreateBody(&bd);

			m_shape1.SetAsBox(0.5f, 1, b2Vec2(-0.9f, 0.0f), 0.0f);
			m_body1->CreateFixture(&m_shape1, 1.0f);

			m_body1->CreateFixture(&circle, 1.0f);

			m_shape2.SetAsBox(1, 0.2f, b2Vec2(-2.2, 0.5f), 0.0f);
			m_body1->CreateFixture(&m_shape2, 1.0f);

			m_shape2.SetAsBox(1, 0.2f, b2Vec2(-2.2, -0.5f), 0.0f);
			m_body1->CreateFixture(&m_shape2, 1.0f);

			m_shape2.SetAsBox(0.2, 0.6f, b2Vec2(-0.7, -1.4f), 0.0f);
			m_body1->CreateFixture(&m_shape2, 1.0f);

			m_shape2.SetAsBox(0.2, 0.6f, b2Vec2(-0.7, 1.4f), 0.0f);
			m_body1->CreateFixture(&m_shape2, 1.0f);

		}
	}

	void newLine(float x, float y, float positionX, float positionY, float rotation, float density, float friction, float restitution, bool dynamic, b2Vec2 force, b2Vec2 vecPos) {
		m_world->SetGravity(b2Vec2(0.0f, -5.0f));
		{
			b2PolygonShape shape;
			shape.SetAsBox(x, y);
			shape.m_radius = 0.1f;



			b2BodyDef bd;
			if (dynamic)
			bd.type = b2_dynamicBody;
			else
				bd.type = b2_staticBody;
			bd.position = b2Vec2(positionX, positionY);
			bd.fixedRotation = rotation;
			b2Body* body = m_world->CreateBody(&bd);
			body->SetTransform(body->GetPosition(), rotation);
			body->CreateFixture(&shape, density);
			body->GetFixtureList()->SetFriction(friction);
			body->GetFixtureList()->SetRestitution(restitution);

				body->ApplyForce(force, vecPos, false);
			
		}

	}

	void newCharacter(float x, float y, float positionX, float positionY, float rotation, float density, float friction, float restitution, bool dynamic) {
		m_world->SetGravity(b2Vec2(0.0f, -5.0f));
		{
			b2PolygonShape shape;
			shape.SetAsBox(x, y);
			shape.m_radius = 0.1f;



			b2BodyDef bd;
			if (dynamic)
				bd.type = b2_dynamicBody;
			else
				bd.type = b2_staticBody;
			bd.position = b2Vec2(positionX, positionY);
			bd.fixedRotation = rotation;
			bodyChar = m_world->CreateBody(&bd);
			bodyChar->SetTransform(bodyChar->GetPosition(), rotation);
			bodyChar->CreateFixture(&shape, density);
			bodyChar->GetFixtureList()->SetFriction(friction);
			bodyChar->GetFixtureList()->SetRestitution(restitution);

			

		}

	}

	void Step(Settings& settings) override
	{
		//Ex 2
		if (firstFrame) {
			newCharacter(0.5, 5, 2, 20, 0, 0.1, 0.1, 0.1, true);
			newLine(0.5,20,-40,20, 0, 0, 0, 0, false, *vec2, *vec2);
			newLine(0.5, 20, 40, 20, 0, 0, 0, 0, false, *vec2, *vec2);
			newLine(40, 0.5, 0, 0, 0, 0, 0, 0, false, *vec2, *vec2);
			newLine(20, 0.5, 0, 35, 25, 0, 0, 0, false, *vec2, *vec2);
			
			newDuck(0, 40, 0, 0.1, 0.1, 0.1, true);

			
			for (int i = 0; i < 6; i++) {
				newLine(0.2, 1, 10 + i * 1, 1.5, 0, 0.5, 0.1, 0.5, true, *vec2, *vec2);
			}
			b2Vec2 *vec1 = new b2Vec2(80, 0);
			b2Vec2 *vecPos = new b2Vec2(0.5, 2);
			newLine(0.2, 1, 9, 1.5, 0, 0.5, 0.1, 0.5, true, *vec1, *vecPos);
			

			firstFrame = false;
		}
		//run the default physics and rendering
		Test::Step(settings);

		//show some text in the main screen
		g_debugDraw.DrawString(5, m_textLine, "Now we have a foo test");
		m_textLine += 15;

		
		
		
	}


	static Test* Create()
	{
		return new MyTest;
	}

	void Keyboard(int key) override
	{
		switch (key)
		{
		case GLFW_KEY_C:
			
			newCircle(0.25, RandomFloat(minX, maxX), RandomFloat(minY, maxY), 10, 1, 1, true, *force);
			break;
		case GLFW_KEY_W:
			
			bodyChar->ApplyForceToCenter(*forceW, false);
			break;
		case GLFW_KEY_A:

			bodyChar->ApplyForceToCenter(*forceA, false);
			break;
		case GLFW_KEY_S:

			bodyChar->ApplyForceToCenter(*forceS, false);
			break;
		case GLFW_KEY_D:

			bodyChar->ApplyForceToCenter(*forceD, false);
			break;
		case GLFW_KEY_3:
			force->x += 200;
			break;
		case GLFW_KEY_2:
			force->x -= 200;
			break;
		}
	}
};
static int testindex = RegisterTest("WillTest", "MyTests", MyTest::Create);
