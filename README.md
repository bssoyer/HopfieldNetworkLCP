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

### The LCP and the Coding Challenge
The LCP relies on a consistent internal representation of the neuron states across all reference patterns. This internal representation must be bipolar (+1/-1). 
One thought that is tempting to apply for the distinctness of pattern representations is to use different symbols to store each pattern—for example, using the ‘*’ character for encoding a circle pattern or using another character, ‘+’, to store another pattern. However, raw symbols like these shall not improve the distinctness or low correlation among the patterns we want to seek. The network doesn’t “see” the original `0`, `+`, or `*` characters. It only sees the final bipolar`(+1/-1)` vectors. The "distinctness" that allows for stable attractors comes from how different these final bipolar vectors are from each other.

The way to improve distinctness is to ensure that the **actual shapes** we want to produce on the grid, which then get converted to `(+1/-1)`vectors, are as different as possible. This means minimizing the number of positions where two distinct patterns have a +1 or a -1. We want their bipolar vector representations to be as close to orthogonal. Using different raw symbols before this bipolar conversion doesn't achieve that mathematical distinctness, but the careful design of the shapes does. Therefore, we must use a consistent bipolar `(+1/-1)`mapping for the "on" and "off" states of all the patterns (see next section for this) when the Hopfield network learning processes them and recalls them. The distinctness comes from the differences in the resulting bipolar vectors, not from using varied initial symbols.


### The Chosen Reference Patterns and Their Implications on Network Performance 
This project addresses this using patterns chosen for their **low mutual correlation**. For example, patterns like:
* A simple geometric shape: a Circle
* Another distinct geometric shape: a Triangle
* A numerical digit: '9'

These shapes have fundamentally different structures, leading to less overlap in their vector representations. This results in:
* A cleaner "energy landscape" with more distinct and stable attractors for each stored pattern.
* Reduced interference between stored memories.
* More robust and accurate recall of the intended patterns from their noisy or incomplete versions.

### Expected Outcome

This `HopfieldNetworkLCP` is expected to reliably store and recall the chosen set of distinct patterns, demonstrating the effectiveness of using low-correlation inputs to improve Hopfield associative memory performance.

---

## Patterns Used


**Example:**

**Pattern 1: '9'** 

### Setting the Environment
Visual Studio Community 2022 is the preferred platform for running this project, which does not use external libraries or open-source software. However, previous releases of Visual Studio (2019, 2017, 2015, etc.) shall not pose any problems with the source code, because the app is written in plain C language.
 Visit https://visualstudio.microsoft.com/tr/downloads/?cid=learn-onpage-download-install-visual-studio-page-cta to install the community edition.
After installing Visual Studio Community 2022, click on the solution file `HopfieldNetwork.sln` to open the development environment. 
Select `> Build > Build HopfieldNetwork`. After the build, you can locate the executable in `C:\...\HopfieldNetwork\x64\Debug` directory.
