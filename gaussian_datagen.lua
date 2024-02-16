-- Function to generate a random number with normal distribution
function generateNormalRandom(mean, deviation)
    local u1 = math.random()
    local u2 = math.random()
    
    local z = math.sqrt(-2 * math.log(u1)) * math.cos(2 * math.pi * u2)
    
    return mean + deviation * z
end

-- Set seed for reproducibility
math.randomseed(os.time())

-- Parameters
local mean = 70
local deviation = 40
local count = 9563
local filename = "random_numbers2.txt"

-- Generate random numbers and write to file
local file = assert(io.open(filename, "w"))

for i = 1, count do
    local number = generateNormalRandom(mean, deviation)
    file:write(number, "\n")
end

file:close()

print("Random numbers generated and saved to " .. filename)

