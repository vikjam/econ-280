#------------#
# Exercise 2 #
#------------#

# Load packages
using Distributions
using StatsBase

# Set random variable
srand(848);

# Set constants
const c   = 0.21;
const ρ   = 0.75;
const μ   = 0;
const σ²  = 0.46;
const μ_y = c / (1 - ρ);

# Part (b)
function rand_ar(T)
	ϵ = rand(Normal(μ, σ²), T);
	y = fill(NaN, T);

	y[1] = μ_y + rand(Normal(μ, σ²));
	for t = 2:T
		y[t] = c + ρ * y[t - 1] + ϵ[t];
	end

	return(y)
end

y_100    = rand_ar(100);
μ_100    = mean(y_100);
γ_100    = autocov(y_100, [1]);
γ_100alt = (1 / (100 - 1)) * (y_100[2:100] - μ_100)' * (y_100[1:99] - μ_100);

# Part (c)
y_10K    = rand_ar(10_000);
μ_10K    = mean(y_10K);
γ_10K    = autocov(y_10K, [1]);
γ_10Kalt = (1 / (10_000 - 1)) * (y_10K[2:10_000] - μ_10K)' * (y_10K[1:(10_000 - 1)] - μ_10K);
