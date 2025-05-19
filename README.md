# HopfieldNetworkLCP: Associative Memory with Low-Correlation Patterns

## Introduction
This project implements a Hopfield network in C to demonstrate its capability as an associative memory. It specifically focuses on the successful storage and recall of multiple patterns by utilizing **Low-Correlation Patterns (LCP)**.

Building upon observations from storing single patterns or multiple highly correlated patterns (which can lead to recall difficulties), this project showcases how choosing distinct, geometrically different patterns significantly improves the network's performance and reliability.

### Background: Hopfield Networks & Hebbian Learning
* **Hopfield Network:** A recurrent neural network with symmetric connections. It functions as a content-addressable memory system, meaning it can retrieve a full stored pattern when presented with a partial or noisy version. The network evolves iteratively, typically settling into a stable state (an attractor) corresponding to a stored memory.
* **Hebbian Learning:** The network is trained using the Hebbian learning principle ("neurons that fire together, wire together"). The synaptic weights between neurons are determined by the correlation of neuron activities across the set of patterns to be memorized. 
For a set of patterns $\{\mu\}$, the weight $w_{ij}$ between neuron $i$ and $j$ is typically calculated as $w_{ij} = \sum_{\mu} x_i^{\mu} x_j^{\mu}$ (where $x_k^{\mu}$ is the bipolar state of neuron $k$ in pattern $\mu$), with $w_{ii}=0$.

### The LCP Strategy: Why Low-Correlation Patterns?
Standard Hopfield networks trained with Hebbian learning have a limited capacity, which is further reduced when the patterns to be stored are highly correlated (i.e., very similar). High correlation leads to "crosstalk" in the weight matrix, resulting in a cluttered energy landscape, poor recall accuracy, and convergence to spurious states.

### The LCP Challenge
The LCP relies on a consistent internal representation of the neuron states across all reference patterns. This internal representation must be bipolar (+1/-1). 
One thought that is tempting to apply for the distinctness of pattern representations is to use different symbols to store each pattern—for example, using the ‘*’ character for encoding a circle pattern or using another character, ‘+’, to store another pattern. However, raw symbols like these shall not improve the distinctness or low correlation among the patterns we want to seek. The network doesn’t “see” the original `0`, `+`, or `*` characters. It only sees the final bipolar`(+1/-1)` vectors. The "distinctness" that allows for stable attractors comes from how different these final bipolar vectors are from each other.

The way to improve distinctness is to ensure that the **actual shapes** we want to produce on the grid, which then get converted to `(+1/-1)` vectors, are as different as possible. This means minimizing the number of positions where two distinct patterns have a +1 or a -1. We want their bipolar vector representations to be as close to orthogonal. Using different raw symbols before this bipolar conversion doesn't achieve that mathematical distinctness, but the careful design of the shapes does. Therefore, we must use a consistent bipolar `(+1/-1)`mapping for the "on" and "off" states of all the patterns (see next section for this) when the Hopfield network learning processes them and recalls them. The distinctness comes from the differences in the resulting bipolar vectors, not from using varied initial symbols.

### The Chosen Reference Patterns and Their Implications on Network Performance and Reliability
**Initial Goal & Early Challenges**: 
The initial goal was to store multiple patterns. Early attempts, for instance, using three visually distinct digit patterns ('1', '4', '9') on an 11x7 grid, resulted in recall failures. It was initially hypothesized that pattern correlation might be the sole major factor.

**Testing with Supposedly Lower Correlation Patterns**:
A set of patterns expected to have lower correlation ('circle', 'triangle', '9') was designed to test this. However, recall failures persisted even with these patterns. This indicated that the problem was likely deeper than just pattern selection and might lie within the core implementation of the Hopfield algorithm.

**The Debugging Breakthrough**: 
A thorough debugging process then uncovered two critical implementation errors:
1. The weight matrix initialization was only clearing the lower triangle, leaving the upper triangle with uninitialized values.
2. The neuron update function (synchronous_update) was not using bipolar (-1/+1) states for neurons when calculating the weighted sum of inputs, which is essential for correct Hopfield dynamics.

**Success After Algorithmic Correction**: 
After these fundamental bugs were corrected, a significant improvement was observed. The network then became capable of reliably storing and recalling multiple patterns. Notably, **the three digits ('1', '4', '9')** and the geometrically distinct shapes ('circle', 'triangle', '9') could be successfully recalled on the 11x7 grid.

**Focus of This LCP Project**: 
While the bug fixes were paramount for any multi-pattern success, this HopfieldNetworkLCP project specifically focuses on demonstrating and analysing the recall of the 'circle', 'triangle', and '9' patterns. These were chosen because, even with a correctly implemented algorithm, using patterns with inherently low mutual correlation remains a key strategy for maximizing the reliability and storage capacity of a Hopfield network trained with standard Hebbian learning.

However, a grid size of `[15x15]`, 225 neurons, intended to store distinct symbols, still failed, despite the corrected algorithm.  The symbolic patterns involved in this experiment, `'@', '?', '&', '%'` on the `[15x15]` grid, the network struggled after only two patterns. 

This outcome suggests that even with a larger network (N=225, theoretical capacity for uncorrelated patterns ~31), the specific bitmap representations of these complex symbols likely still possess sufficient underlying correlation or feature overlap to challenge the standard Hebbian learning rule's ability to form distinct and stable attractors for all four.

The process of superimposing multiple complex patterns seems to lead to a very intricate energy landscape where small basins of attraction or spurious minima become dominant for some inputs. It highlights the sensitivity of the basic Hopfield model to the nature and number of patterns being stored, even when visual distinctiveness is attempted.
Overall, the project demonstrates both the Hopfield network's capabilities and well-known limitations, particularly the impact of pattern correlation and the challenges in scaling storage with complex patterns using simple Hebbian learning.

### Expected Outcome

This HopfieldNetworkLCP successfully demonstrates the reliable storage and recall of the chosen set of distinct patterns (Circle, Triangle, '9'), showcasing the effectiveness of using low-correlation inputs.

## Pattern Designs

### The Circle Pattern ###

| Reference Pattern | Distorted Pattern |
|-------------------|-------------------|
|0  0  0  0  0  0  0|0  0  0  0  0  0  0|
|0  0  0  0  0  0  0|0  0  0  0  0  0  0|
|0  0  1  1  1  0  0|0  0  1  0  1  0  0|
|0  1  0  0  0  1  0|0  1  0  0  0  1  0|
|1  0  0  0  0  0  1|1  0  0  1  0  0  1|
|1  0  0  0  0  0  1|0  0  1  0  0  0  0|
|1  0  0  0  0  0  1|1  0  0  0  1  0  1|
|0  1  0  0  0  1  0|0  1  0  0  0  0  0|
|0  0  1  1  1  0  0|0  0  0  0  1  0  0|
|0  0  0  0  0  0  0|0  0  0  0  0  0  0|
|0  0  0  0  0  0  0|0  0  0  0  0  0  0|

### The Triangle Pattern ###

| Reference Pattern | Distorted Pattern |
|-------------------|-------------------|
|0  0  0  0  0  0  0|0  0  0  0  0  0  0|
|0  0  0  0  1  0  0|0  0  0  0  1  0  0|
|0  0  0  1  1  0  0|0  0  0  1  1  0  0|
|0  0  1  0  1  0  0|0  0  1  0  0  0  0|
|0  1  0  0  1  0  0|0  0  0  0  0  0  0|
|1  0  0  0  1  0  0|1  0  1  0  1  0  0|
|0  1  0  0  1  0  0|0  0  0  0  1  0  0|
|0  0  1  0  1  0  0|0  0  1  0  0  0  0|
|0  0  0  1  1  0  0|0  0  0  0  0  0  0|
|0  0  0  0  1  0  0|0  0  0  0  1  0  0|
|0  0  0  0  0  0  0|0  0  0  0  0  0  0|


### The Digit Pattern '9' ###

| Reference Pattern | Distorted Pattern |
|-------------------|-------------------|
|0  1  1  1  1  1  0|0  1  0  0  1  1  0|
|1  0  0  0  0  0  1|1  0  0  0  0  0  1|
|1  0  0  0  0  0  1|1  0  0  0  0  0  1|
|1  0  0  0  0  0  1|0  0  0  0  0  0  0|
|1  0  0  0  0  0  1|1  0  0  0  0  0  1|
|0  1  1  1  1  0  0|0  0  1  0  1  1  0|
|0  0  0  0  0  0  1|0  1  0  0  0  0  0|
|0  0  0  0  0  0  1|0  0  1  0  1  0  0|
|0  0  0  0  0  0  1|0  0  0  0  0  0  1|
|0  0  0  0  0  0  1|0  0  0  0  0  0  1|
|0  1  1  1  1  1  0|0  1  0  0  1  1  0|

### Setting the Environment
Visual Studio Community 2022 is the preferred platform for running this project, which does not use external libraries or open-source software. However, previous releases of Visual Studio (2019, 2017, 2015, etc.) shall not pose any problems with the source code, because the app is written in plain C.
 
Please, visit https://visualstudio.microsoft.com/tr/downloads/?cid=learn-onpage-download-install-visual-studio-page-cta to install the community edition.

After installing Visual Studio Community 2022, click on the solution file `HopfieldNetHebbian.sln` to open the development environment. Select `> Build > Build HopfieldNetworkLCP`. After the build, you can typically locate the executable in a subdirectory like `C:\...\HopfieldNetworkLCP\x64\Debug`.
