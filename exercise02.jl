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
    [y[t] = c + ρ * y[t - 1] + ϵ[t] for t in 1:T]
    return(y)
end

function compute_autocov(T)
    y    = rand_ar(T)
    μ    = mean(y)
    γ    = autocov(y, [1])
    γalt = (1 / (T - 1)) * dot(y[2:T] - μ, y[1:T-1] - μ)
    return (γ, γalt)
end

compute_autocov(100)

# Part (c)
compute_autocov(10_000)
