#include <unity.h>


void starts_with_empty_action_registry() {
    TEST_PASS();
}

void execute_tests() {
    UNITY_BEGIN();

    RUN_TEST(starts_with_empty_action_registry);

    UNITY_END();
}

#ifdef ARDUINO

#include <Arduino.h>

void setup() {
    execute_tests();
}

void loop() {
}

#else

int main(int argc, char **argv) {
    execute_tests();
    return 0;
}

#endif
