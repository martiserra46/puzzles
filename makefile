all: puzzle generate_levels

puzzle: main.o bundle.o text_utils.o number_utils.o system_utils.o vector_utils.o input.o input_validator.o input_converter.o action.o input_action.o position.o figure.o grid.o drawing_generator.o puzzle.o puzzle_generator.o main_menu_controller.o game_controller.o screen.o puzzles_file_manager.o
	g++ main.o bundle.o text_utils.o number_utils.o system_utils.o vector_utils.o input.o input_validator.o input_converter.o action.o input_action.o position.o figure.o grid.o drawing_generator.o puzzle.o puzzle_generator.o main_menu_controller.o game_controller.o screen.o puzzles_file_manager.o -o puzzle -std=c++11

generate_levels: generate_levels.o puzzle.o grid.o figure.o position.o puzzle_generator.o puzzles_file_manager.o number_utils.o vector_utils.o
	g++ generate_levels.o puzzle.o grid.o figure.o position.o puzzle_generator.o puzzles_file_manager.o number_utils.o vector_utils.o -o generate_levels -std=c++11

main.o: main.cpp
	g++ -c main.cpp -std=c++11

generate_levels.o: generate_levels.cpp
	g++ -c generate_levels.cpp -std=c++11

bundle.o: bundle.cpp
	g++ -c bundle.cpp -std=c++11

text_utils.o: text_utils.cpp
	g++ -c text_utils.cpp -std=c++11

number_utils.o: number_utils.cpp
	g++ -c number_utils.cpp -std=c++11

system_utils.o: system_utils.cpp
	g++ -c system_utils.cpp -std=c++11

vector_utils.o: vector_utils.cpp
	g++ -c vector_utils.cpp -std=c++11

input.o: input.cpp
	g++ -c input.cpp -std=c++11

input_validator.o: input_validator.cpp
	g++ -c input_validator.cpp -std=c++11

input_converter.o: input_converter.cpp
	g++ -c input_converter.cpp -std=c++11

action.o: action.cpp
	g++ -c action.cpp -std=c++11

input_action.o: input_action.cpp
	g++ -c input_action.cpp -std=c++11

position.o: position.cpp
	g++ -c position.cpp -std=c++11

figure.o: figure.cpp
	g++ -c figure.cpp -std=c++11

grid.o: grid.cpp
	g++ -c grid.cpp -std=c++11

puzzle.o: puzzle.cpp
	g++ -c puzzle.cpp -std=c++11

drawing_generator.o: drawing_generator.cpp
	g++ -c drawing_generator.cpp -std=c++11

puzzle_generator.o: puzzle_generator.cpp
	g++ -c puzzle_generator.cpp -std=c++11

main_menu_controller.o: main_menu_controller.cpp
	g++ -c main_menu_controller.cpp -std=c++11

game_controller.o: game_controller.cpp
	g++ -c game_controller.cpp -std=c++11

screen.o: screen.cpp
	g++ -c screen.cpp -std=c++11

puzzles_file_manager.o: puzzles_file_manager.cpp
	g++ -c puzzles_file_manager.cpp -std=c++11

clean:
	rm *.o puzzle