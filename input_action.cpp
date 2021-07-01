#include "input_action.h"
#include <string>
#include "bundle.h"
#include <utility>

InputAction::InputAction(Input *input, Action *action) : input(input), action(action) {}

InputAction::~InputAction()
{
    delete input;
    delete action;
}

void InputAction::do_input_action()
{
    std::pair<std::string, Bundle> input_value = input->input();
    action->do_action(input_value.first, input_value.second);
}