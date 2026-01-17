#define NOMINMAX
#include <torch/torch.h>
#include <torch/nn/module.h>

#define GETVARNAME(v) static_cast<std::string>(#v)

struct PathNet {
	torch::nn::Conv2d conv1 {nullptr}, conv2{nullptr};
	torch::nn::Linear dataCenter1{nullptr}, dataCenter2{nullptr};

	PathNet(){
		conv1 = register_module(GETVARNAME(conv1), torch::nn::Conv2dOptions(3, 16, 3).padding(1));
		
	}
};