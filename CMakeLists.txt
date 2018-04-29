# cmake_minimum_required(VERSION <specify CMake version here>)
project(team37 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(team37
        Button/grovepi_button.c
        Buzzer/grovepi_buzzer.c
        Feuchtigkeitssensor/humidity.c
        LCD/lcd_test_example.c
        LED/grovepi_led.c
        LED-PWM/grovepi_pwm_led.c
        Light-sensor/light_sensor.c
        "PIR-motion sensor/pir_motion_sensor.c"
        Potentiometer/grovepi_rotaryAngle.c
        Sound-Sensor/grovepi_sound.c
        "Temperatur und Luftfeuchtigkeit/temp_hum.c"
        Ultraschall-Abstandssensor/grovepi_us_read.c
        grovepi.c
        grovepi.h
        grovepi_analog_read.c
        grovepi_analog_write.c
        grovepi_digital_read.c
        grovepi_digital_write.c
        schritt1.c
        server.c)
