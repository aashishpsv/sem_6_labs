__kernel void reverse_words(__global char *inputString, __global char *outputString, __global int *wordLengths, int numWords) {
    int globalId = get_global_id(0);
    
    // Get the length of the current word
    int wordLength = wordLengths[globalId];
    
    // Calculate the starting index of the current word in the input string
    int wordStartIndex = 0;
    for (int i = 0; i < globalId; i++) {
        wordStartIndex += wordLengths[i];
        // Skip any non-alphanumeric characters after each word
        while (inputString[wordStartIndex] != ' ' && inputString[wordStartIndex] != '\0') {
            wordStartIndex++;
        }
        // Skip any spaces between words
        while (inputString[wordStartIndex] == ' ') {
            wordStartIndex++;
        }
    }
    
    // Reverse the current word and store it in the output string
    for (int i = 0; i < wordLength; i++) {
        outputString[wordStartIndex + i] = inputString[wordStartIndex + wordLength - i - 1];
    }
    
    // Add a space at the end of the reversed word
    outputString[wordStartIndex + wordLength] = ' ';
}
