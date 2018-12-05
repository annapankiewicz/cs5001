# Anna Pankiewicz
# CS5001 Homework #1

import random, sys

def main():
    # seed random
    seed = random.randrange(sys.maxsize)
    random.seed(seed)

    # read in trash data
    mass, price = read('trashdata.txt')

    # read in validation data
    validate_mass, validate_price = read('moretrashdata.txt')

    # initially set learning rate to 0.0001
    eta = 0.0001

    # initialize w0 and w1 randomly in set range
    w0 = random.randint(0,100)
    w1 = random.randint(0,100)

    # incremental linear learner
    for iteration in range(0, 5000):
        for example in range(0, len(mass)):
            # make prediction
            y_cap = w0 + (w1 * mass[example])
            # compare actual value & prediction
            delta = price[example] - y_cap
            # update weights incrementally
            w0 = w0 + eta * delta * mass[example]
            w1 = w1 + eta * delta * mass[example]

    # try weights on validation data
    predictions = []
    for example in range(0, len(validate_price)):
        y_cap = w0 + (w1 * validate_mass[example])
        delta = price[example] - y_cap
        predictions.append(y_cap)

    # calculate SSE error from the validation data predictions
    error = sse(validate_price, predictions)
    
    # we done
    results(seed, w0, w1, eta, error)

def read(filename):
    """ 
    Reads in mass/price data from a file.

    Args:
        filename (string): file to read data from

    Returns:
        inputs (list of ints): mass values of the data
        outputs (list of floats): price values of the data
    """
    inputs = []
    outputs = []
    with open(filename, 'r') as f:
        for line in f:
            x_value, y_value = line.split()
            inputs.append(int(x_value))
            outputs.append(float(y_value))
    return inputs, outputs
        

def sse(examples, predictions):
    """
    Calculates the sum of squares error of the learner's predictions.

    Args:
        examples (list): list of correct price values
        predictions (list): list of predicted price values

    Returns:
        error (float): SSE error of predictions
    """
    error = 0
    for i in range(0, len(examples)):
        error += (examples[i] - predictions[i]) * (examples[i] - predictions[i])
    return error

def results(seed_value, w0, w1, eta, error):
    """
    Takes final data and writes with correct formatting to learner1output.txt.

    Args:
        seed_value (int): what was used to seed the rng
        w0 (float): final weight 0 value
        w1 (float): final weight 1 value
        eta (float): learning rate for the learner
        error (float): sum of squares error of the learner
    Returns:
        None
    """
    with open("learner1output.txt", "w") as f:
        f.write("CS5001: HW#1\nProgrammer: Anna Pankiewicz\n\n")
        f.write("TRAINING\nUsing random seed = {0}\n".format(seed_value))
        f.write("Using learning rate eta = {0}\n".format(eta))
        f.write("After 5000 iterations:\nWeights:\n")
        f.write("w0 = {0}\n".format(w0))
        f.write("\nw1 = {0}\n".format(w1))
        f.write("\nVALIDATION\nSum-of-Squares Error: {0}".format(error))

if __name__ == "__main__":
    main()