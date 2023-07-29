### Shamir's Secret Sharing (SSS)

- The ``` plain.cpp ``` contains the direct implementation of the SSS scheme based on the research paper written bby Adi Shamir. THe link for the research paper : [How to Share a secret](https://web.mit.edu/6.857/OldStuff/Fall03/ref/Shamir-HowToShareASecret.pdf)
- The ```SSS_IN_FIELD.cpp``` contains the implementation that works for real time huge numbers. This is being done with the help of Modulo-mathematics (For dealing with huge numbers).
- Explanation of different functions implemented: 
    1. ``` vector<int>generateRandomPoly(int k) ```