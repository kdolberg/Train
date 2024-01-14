#include "main.h"

int main(int argc, char * const argv[]) {
	print_compile_date();

	ArgumentOptionOutputs options = parse_command_line_arguments(argc,argv);

	if (options.learning_rate_user_defined) {
		options.n.learning_rate = options.learning_rate;
		std::cout << "The user-defined learning rate is ";
	} else {
		options.learning_rate = options.n.learning_rate;
		std::cout << "The learning rate loaded from the neural net file is ";
	}
	std::cout << options.learning_rate << ".\n";
	
	if (options.dynamic_learning_rate) {
		std::cout << "Dynamic learning rate with filter length ";
		std::cout << options.filter_length << ", and meta learning rate ";
		std::cout << options.meta_learning_rate << std::endl;
	}

	options.n.load_training_data(options.td);

	Filter f1(options.filter_length),f2(options.filter_length);

	options.n.forward_propagate();
	ml::scalar h = 1e-6;

	// Setup timers and error intervals
	Timer t_print_interval,t_whole_procss;
	ml::scalar E=options.n.error(),delta_E_avg_plus_h,delta_E_avg_nominal;
	ml::scalar Erms = sqrt(2*E);
	ErrorInterval e_metalearning(&E),e_output(&Erms);
	e_output.start();
	t_print_interval.start();
	t_whole_procss.start();

	for (ml::uint i = 0; (i < options.num_epochs) && (Erms > options.min_error); ++i) {
		options.learning_rate = std::max(options.learning_rate,options.min_learning_rate);

		options.n.learning_rate = ((options.dynamic_learning_rate && i%2) ? options.learning_rate+h : options.learning_rate);

		e_metalearning.start();
		E = options.n.learn();
		e_metalearning.stop();

		if((i % options.print_interval)==0 && i!=0) {
			e_output.start();
			Erms = sqrt(2*E);
			std::cout << std::setw(WIDTH_BETWEEN/2) << std::setfill(' ') << i << ":";
			PRINT2(options.learning_rate,"lr")
			PRINT1(Erms);
			PRINT2(t_print_interval.stop().delta() << " seconds","Dur");
			PRINT2(e_output.stop().delta(),"dErms")
			PRINT2(e_output.delta()/t_print_interval.delta() << " Hz","dErms/dt");
			std::cout << std::endl;
			train::save(options.n,options.output_net_filename.c_str());
			std::cout << std::setw(0);

			// Lastly, restart the intervals.
			e_output.start();
			t_print_interval.start();
		}

		if (options.dynamic_learning_rate && i%2) {
			delta_E_avg_plus_h = f1(e_metalearning.delta());
		} else {
			delta_E_avg_nominal = f2(e_metalearning.delta());
		}

		if(options.dynamic_learning_rate && i > options.filter_length) {
			options.learning_rate += options.meta_learning_rate*(delta_E_avg_plus_h/h - delta_E_avg_nominal/h);
		}
	// }
	// std::cout << "Training complete.\n";
	// if(train::save(n,output_net_filename.c_str())) {
	// 	std::cout << "Saved neural net as \"" << output_net_filename.c_str() << "\".\n";
	// } else {
	// 	std::cerr << "Could not save neural net as \"" << output_net_filename.c_str() << "\".\n";
	// 	return 1;
	// }
	// } catch (std::exception& e) {
	// 	std::cerr << "ERROR: " << e.what() << std::endl;
	// 	return -1;
	}
	return 0;
}