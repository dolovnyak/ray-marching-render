cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0076 NEW)

target_sources(rt PUBLIC
        main.c
        initialization.c
        ray_marching_render.c
        ../utilits/math_vec1.c
        ../utilits/math_vec2.c
        rt_physics_system.c
        )