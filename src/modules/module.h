#include <string>

#include <Eigen/Dense>

struct Port
{
    std::string name;
    void put(Eigen::MatrixXcd input) { state = input; }
    Eigen::MatrixXcd get() const { return state; }

    std::tuple<size_t, size_t> getDims() { return {state.rows(), state.cols()}; }

    Port(size_t rows, size_t cols)
    {
        state = Eigen::MatrixXcd(rows, cols);
    }

private:
    Eigen::MatrixXcd state;
};

struct Module
{
    enum class Type
    {
        Generator,
        FFT,
        Unknown
    };

    Type type;
    size_t id;

    std::vector<Port> inputs;
    std::vector<Port> outputs;
};