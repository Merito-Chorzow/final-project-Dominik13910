#include <unity.h>
#include "FanController.h"
#include "FanController.cpp"

FanController controller;

void test_init_state(void) {
    controller.init();
    TEST_ASSERT_EQUAL(FanController::State::IDLE, controller.getState());
}

void test_fault_on_invalid_temp(void) {
    controller.update(0);
    TEST_ASSERT_EQUAL(FanController::State::FAULT, controller.getState());
}

void test_recovery_from_fault(void) {
    controller.update(0);
    controller.update(2000);
    TEST_ASSERT_NOT_EQUAL(FanController::State::FAULT, controller.getState());
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_init_state);
    RUN_TEST(test_fault_on_invalid_temp);
    RUN_TEST(test_recovery_from_fault);
    UNITY_END();
}

void loop() {}
