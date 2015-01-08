#include "firstpersoncontrol.hpp"

#include "input.hpp"
#include "spatial.hpp"

gst::FirstPersonControl::FirstPersonControl()
    : rotation_speed(2.8f),
      movement_speed(5.0f),
      yaw_angle(0.0f),
      pitch_angle(0.0f)
{
}

void gst::FirstPersonControl::update(seconds dt, Input const & input, Spatial & spatial)
{
    rotate(dt, input, spatial);
    move(dt, input, spatial);
}

void gst::FirstPersonControl::rotate(seconds dt, Input const & input, Spatial & spatial)
{
    const glm::vec2 mouse_movement(
        -input.position_rel().x,
        -input.position_rel().y
    );

    const float speed = rotation_speed * dt.count();

    // -90 <= pitch <= 90
    pitch_angle += mouse_movement.y * speed;
    pitch_angle = glm::clamp(pitch_angle, -90.0f, 90.0f);
    glm::quat pitch = glm::angleAxis(pitch_angle, X_UNIT);

    // -360 <= yaw <= 360
    yaw_angle += mouse_movement.x * speed;
    if (yaw_angle < -360.0f) {
        yaw_angle += 360.0f;
    } else if (yaw_angle > 360.0f) {
        yaw_angle -= 360.0f;
    }
    glm::quat yaw = glm::angleAxis(yaw_angle, Y_UNIT);

    spatial.orientation = glm::normalize(yaw * pitch);
}

void gst::FirstPersonControl::move(seconds dt, Input const & input, Spatial & spatial)
{
    const float speed = movement_speed * dt.count();

    glm::vec3 displacement(0.0f);

    if (input.down(Key::W) || input.down(Key::UP)) {
        displacement.z--;;
    }

    if (input.down(Key::S) || input.down(Key::DOWN)) {
        displacement.z++;
    }

    if (input.down(Key::A) || input.down(Key::LEFT)) {
        displacement.x--;
    }

    if (input.down(Key::D) || input.down(Key::RIGHT)) {
        displacement.x++;
    }

    if (input.down(Key::Q)) {
        displacement.y--;
    }

    if (input.down(Key::R)) {
        displacement.y++;
    }

    if (displacement != glm::vec3(0.0f)) {
        // limit translation to the xz-plane
        glm::quat yaw = spatial.orientation;
        yaw.x = 0.0f;
        yaw.z = 0.0f;
        yaw = glm::normalize(yaw);
        spatial.position += yaw * (glm::normalize(displacement) * speed);
    }
}
