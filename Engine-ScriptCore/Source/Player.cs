using System;

using ENGINE;


namespace Sandbox
{

    public class Player : Entity
    {

        void OnCreate()
        {
            Console.WriteLine($"Player.OnCreate - {ID}");
        }


        void OnUpdate(float ts)
        {
            Console.WriteLine($"Player.OnUpdate: {ts}");

            float speed = 0.8f;
            Vector3 velocity = Vector3.Zero;

            //Vector3 translation = Translation;
            //translation.X += speed * ts;
            //Translation = translation;

            if (Input.IsKeyDown(KeyCode.W))
                velocity.Y = 1.0f;
            else if (Input.IsKeyDown(KeyCode.S))
                velocity.Y = -1.0f;
            if (Input.IsKeyDown(KeyCode.A))
                velocity.X = -1.0f;
            else if (Input.IsKeyDown(KeyCode.D))
                velocity.X = 1.0f;

            velocity *= speed;
            Vector3 translation = Translation;
            translation += velocity * ts;
            Translation = translation;
        }
    }


}