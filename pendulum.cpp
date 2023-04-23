#include <cmath>
#include <iostream>
#include <fstream>
#include <cassert>
#include <exception>
#include <stdexcept>
#include <type_traits>
#include <initializer_list>
#include <memory>


template<typename T>
class Vector {
private:
	int length;
	T* data;

public:
	// Constructors and destructor
	Vector() {
		this->length = 0;
		this->data = nullptr;
	}

	Vector(int n) {
		this->length = n;
		this->data = new T[n];

		// Initialize elements of the vector to 0
		for (int i = 0; i < n; i++) {
			this->data[i] = 0;
		}
	}

	Vector(std::initializer_list<T> init_lst) {
		this->length = init_lst.size();
		this->data = new T[this->length];
		std::uninitialized_copy(init_lst.begin(), init_lst.end(), this->data);
	}

	Vector(const Vector& other) {
		this->length = other.length;
		this->data = new T[this->length];

		for (int i = 0; i < other.length; i++) {
			this->data[i] = other.data[i];
		}
	}

	Vector(Vector&& other) {
		this->length = other.len();
		this->data = new T[this->length];

		for (int i = 0; i < other.length; i++) {
			this->data[i] = other.data[i];
		}
	}

	~Vector() {
		this->length = 0;
		delete[] this->data;
		this->data = nullptr;
	}

	// Operators
	template<typename V>
	Vector<std::common_type_t<T, V>> operator+(const Vector<V>& other) const {
		if (this->length != other.length) {
			throw std::invalid_argument("Length Error: Vectors must be of equal length.");
		}

		Vector<std::common_type_t<T, V>> return_vector = Vector<std::common_type_t<T, V>>(2);
		for (int i = 0; i < this->length; i++) {
			return_vector[i] = this->data[i] + other.data[i];
		}
		return return_vector;
	}

	T& operator[](const int index) const {
		return this->data[index];
	}

	Vector& operator=(const Vector& other) {
		if (this == &other) {
			return *this;
		}

		delete[] this->data;
		this->length = other.len();
		this->data = new T[this->length];

		for (int i = 0; i < other.len(); i++) {
			this->data[i] = other[i];
		}
		return *this;
	}

	Vector& operator=(Vector&& other) {
		if (this == &other) {
			return *this;
		}

		delete[] this->data;
		this->length = 0;

		this->length = other.len();
		this->data = new T[other.len()];
		for (int i = 0; i < other.len(); i++) {
			this->data[i] = other[i];
		}

		delete[] other.data;
		other.data = nullptr;
		other.length = 0;

		return *this;
	}

	// Getters and Setters
	int len() const {
		return this->length;
	}
};

template<typename U, typename T>
Vector<std::common_type_t<T, U>> operator*(const Vector<T>& vector, const U scalar) {
	Vector<std::common_type_t<T, U>> return_vector(vector.length);
	for (int i = 0; i < return_vector.length; i++) {
		return_vector[i] = vector[i]*scalar;
	}
	return return_vector;
}

template<typename U, typename T>
Vector<std::common_type_t<T, U>> operator*(const U scalar, const Vector<T>& vector) {
	Vector<std::common_type_t<T, U>> return_vector(vector.len());
	for (int i = 0; i < return_vector.len(); i++) {
		return_vector[i] = vector[i]*scalar;
	}
	return return_vector;
}


template<typename T>
class Pendulum {
private:
	T mu;
	T mass;
	T length;
	T I;
	double g;

public:
	Pendulum(const T mass, const T length) {
		this->mu = 0;
		this->mass = mass;
		this->length = length;
		this->I = mass*length*length;
		this->g = 9.81;
	}

	Pendulum(const T mass, const T length, const T mu): Pendulum(mass, length) {
		this->mu = mu;
	}

	~Pendulum() { }

	// Methods
	Vector<double> equation_of_motion(const Vector<double>& state) const {
		/**
		 * state is a Vector of 2 for which
		 * state[0] = θ
		 * state[1] = dθ/dt
		 *
		 * returns a vector also containing 2 elements of the form
		 * state_derivative[0] = dθ/dt
		 * state_derivative[1] = d2θ/dt2
		 *
		 * State derivative is computed using the equation of motion
		 * d2θ/dt2 = -1/(ml)*dθ/dt - g/l*sin(θ)
		*/
		const double theta = state[0];
		const double theta_dot = state[1];
		const double theta_ddot = -this->mu/(this->mass*this->length)*theta_dot - (this->g/this->length)*std::sin(theta);

		Vector<double> return_vector = {theta_dot, theta_ddot};
		return return_vector;
	}

	Vector<double> convert_to_xy(const Vector<double> state) {
		const double theta = state[0];
		const double x = this->length*std::sin(theta);
		const double y = this->length*std::cos(theta);
		Vector<double> return_vector = {x, y};

		return return_vector;
	}

	Vector<double> convert_to_xy(const double theta) {
		const double x = this->length*std::sin(theta);
		const double y = this->length*std::cos(theta);
		Vector<double> return_vector = {x, y};

		return return_vector;
	}

	void info() const {
		std::cout << "----------------------------------------------" << std::endl;
		std::cout << "Info on the Pendulum being simulated" << std::endl;
		std::cout << "----------------------------------------------" << std::endl;
		std::cout << "μ = " << this->mu << std::endl;
		std::cout << "m = " << this->mass << std::endl;
		std::cout << "l = " << this->length << std::endl;
		std::cout << "I = " << this->I << std::endl << std::endl;
	}
};


class Solver {
private:
	double t0;
	double tf;
	double h;
	int N;


public:
	Solver(const double t0, const double tf, const double h) {
		this->t0 = t0;
		this->tf = tf;
		this->N = (int)((tf - t0)/h);
		this->h = h;
	}

	Solver(const double t0, const double tf, const int N) {
		this->t0 = t0;
		this->tf = tf;
		this->N = N;
		this->h = (double)((tf - t0)/(double)(N));
	}

	// Methods
	// Can make this implementation more generic by replacing Pendulum<T>& pendulum with a 
	// dynamical systems abstract base class. This method should be a base for dynamical systems such
	// as a pendulum and have a purely virtual method for equations of motion.
	template<typename T>
	void forward_euler(Pendulum<T>& pendulum,
					const double theta0,
					const double theta_dot0) const {
		// Setting up the file for writing the output data
		std::ofstream data_file;
		data_file.open("data_fe.csv");
		data_file << "t,theta,theta_dot,x,y\n";

		Vector<double> initial_conditions({theta0, theta_dot0});
		Vector<double> current_state = initial_conditions;

		std::cout << "----------------------------------------------" << std::endl;
		std::cout << "Solver Parameters" << std::endl;
		std::cout << "step size = " << h << std::endl;
		std::cout << "t0 = " << t0 << std::endl;
		std::cout << "tf = " << tf << std::endl;
		std::cout << "N = " << N << std::endl;
		std::cout << "-----------------------------------------------" << std::endl;
		std::cout << "Starting with the following initial conditions:" << std::endl;
		std::cout << "theta = " << initial_conditions[0] << std::endl;
		std::cout << "dtheta/dt = " << initial_conditions[1] << std::endl;
		std::cout << "-----------------------------------------------" << std::endl;

		for (int i = 0; i < this->N; i++) {
			Vector<double> state_derivative = pendulum.equation_of_motion(current_state);
			Vector<double> new_state = current_state + this->h*state_derivative;
			Vector<double> xy_position = pendulum.convert_to_xy(new_state);

			data_file << i*this->h << ","
					<< new_state[0] << ","
					<< new_state[1] << ","
					<< xy_position[0] << ","
					<< xy_position[1] << std::endl;

			current_state = new_state;
		}

		// Closing the file handle
		data_file.close();
	}

	template<typename T>
	void rk4(Pendulum<T> pendulum,
		  const double theta0,
		  const double theta_dot0) const {
		// Setting up the file for writing the output data
		std::ofstream data_file;
		data_file.open("data_rk4.csv");
		data_file << "t,theta,theta_dot,x,y\n";


		Vector<double> initial_conditions = {theta0, theta_dot0};
		Vector<double> current_state = initial_conditions;
		Vector<double> new_state;
		Vector<double> w0, k1, k2, k3, k4;

		std::cout << "----------------------------------------------" << std::endl;
		std::cout << "Solver Parameters" << std::endl;
		std::cout << "step size = " << h << std::endl;
		std::cout << "t0 = " << t0 << std::endl;
		std::cout << "tf = " << tf << std::endl;
		std::cout << "N = " << N << std::endl;
		std::cout << "-----------------------------------------------" << std::endl;
		std::cout << "Starting with the following initial conditions:" << std::endl;
		std::cout << "theta = " << initial_conditions[0] << std::endl;
		std::cout << "dtheta/dt = " << initial_conditions[1] << std::endl;
		std::cout << "-----------------------------------------------" << std::endl;

		for (int i = 0; i < this->N; i++) {
			w0 = current_state;
			k1 = this->h*pendulum.equation_of_motion(current_state);
			k2 = this->h*pendulum.equation_of_motion(current_state + 0.5*k1);
			k3 = this->h*pendulum.equation_of_motion(current_state + 0.5*k2);
			k4 = this->h*pendulum.equation_of_motion(current_state + k3);

			new_state = current_state + 1/6*(k1 + 2*k2 + 2*k3 + k4);
			Vector<double> xy_position = pendulum.convert_to_xy(new_state);

			data_file << i*this->h << ","
					<< new_state[0] << ","
					<< new_state[1] << ","
					<< xy_position[0] << ","
					<< xy_position[1] << std::endl;

			current_state = new_state;
		}
		
		// Closing the file handle
		data_file.close();
	}
};


int main() {
	Pendulum<double> pendulum = Pendulum<double>(1.0, 1.0, 0.3);
	pendulum.info();
	Solver pendulum_solver = Solver(0.0, 25.0, 1000000);

	const double theta0 = M_PI;
	const double theta_dot0 = 10;
	pendulum_solver.forward_euler(pendulum, theta0, theta_dot0);
	pendulum_solver.rk4(pendulum, theta0, theta_dot0);
}
