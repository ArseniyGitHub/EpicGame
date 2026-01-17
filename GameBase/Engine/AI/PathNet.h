#define NOMINMAX
#include <torch/torch.h>
#include <torch/nn/module.h>

#define GETVARNAME(v) static_cast<std::string>(#v)

struct PathNet : torch::nn::Module {
	torch::nn::Conv2d conv1 {nullptr}, conv2{nullptr};
	torch::nn::Linear dataCenter1{nullptr}, dataCenter2{nullptr};
	

	PathNet(){
		conv1 = register_module(GETVARNAME(conv1), torch::nn::Conv2d(torch::nn::Conv2dOptions(3, 16, 3).padding(1)));
		conv2 = register_module(GETVARNAME(conv2), torch::nn::Conv2d(torch::nn::Conv2dOptions(16, 32, 3).padding(1)));
		dataCenter1 = register_module(GETVARNAME(dataCenter1), torch::nn::Linear(15 * 15 * 32, 128));
		dataCenter2 = register_module(GETVARNAME(dataCenter2), torch::nn::Linear(128, 4));
	}

	torch::Tensor forward(torch::Tensor x) {
		x = torch::relu(conv1->forward(x));
		x = torch::relu(conv2->forward(x));
		x = x.view({ x.size(0), -1 });
		x = torch::relu(dataCenter1->forward(x));
		return torch::log_softmax(dataCenter2->forward(x), 1);
	}
};