#include <cmath>
#include <iostream>
#include <cassert>
#include <exception>
#include <stdexcept>
#include <initializer_list>
#include <memory>

#include <math.h>
#include <stdexcept>
#include <type_traits>


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

	Vector(const int n) {
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

	Vector(Vector<T>& other) {
		this->length = other.length;
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

		Vector<std::common_type_t<T, V>> return_vector(2);
		for (int i = 0; i < this->length; i++) {
			return_vector[i] = this->data[i] + other.data[i];
		}
		return return_vector;
	}

	T& operator[](const int index) const {
		return this->data[index];
	}
};

template<typename U, typename T>
Vector<std::common_type_t<T, U>> operator*(const Vector<T>& vector, const U scalar) {
	Vector<std::common_type_t<T, U>> return_vector(vector.length);
	for (int i = 0; i < return_vector.length; i++) {
		return_vector.data[i] = vector.data[i]*scalar;
	}

	return return_vector;
}

template<typename U, typename T>
Vector<std::common_type_t<T, U>> operator*(const U scalar, const Vector<T>& vector) {
	Vector<std::common_type_t<T, U>> return_vector(vector.length);
	for (int i = 0; i < return_vector.length; i++) {
		return_vector.data[i] = vector.data[i]*scalar;
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

public:
	Pendulum(const T mass, const T length, const double g = 9.81) {
		this->mu = 0;
		this->mass = mass;
		this->length = length;
		this->I = mass*length*length;
		this->g = g;
	}

	Pendulum(const T mass, const T length, const T mu): Pendulum(mass, length) {
		this->mu = mu;
	}

	~Pendulum() { }

	// Methods
	Vector<double> equation_of_motion(const Vector<double> state) const {
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
		 * d2θ/dt2 = 1/(ml)*dθ/dt - g/l*sin(θ)
		*/
		const double theta = state[0];
		const double theta_dot = state[1];

		const double theta_ddot = this->mu/(this->m*this->length)*theta_dot - (this->g/this->length)*std::sin(theta);

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
		this->h = h;
		this->N = (int)((tf - t0)/h);
	}
	Solver(const double t0, const double tf, const int N) {
		this->t0 = t0;
		this->tf = tf;
		this->N = N;
		this->h = (double)((tf - t0)/(double)(N));
	}

	// Methods
	template<typename T>
	void forward_euler(Pendulum<T> pendulum,
					const double theta0,
					const double theta_dot0) const {
		const Vector<double> initial_conditions({theta0, theta_dot0});
		Vector<double> current_state(2);
		Vector<double> new_state(2);

		for (int i = 0; i < N; i++) {
			new_state = current_state + h*pendulum.equation_of_motion(current_state);
			std::cout << "theta = " << new_state[0] << std::endl;
			std::cout << "dtheta/dt = " << new_state[1] << std::endl;
		}
	}

	void rk4() const { }
};


int main() {

}
