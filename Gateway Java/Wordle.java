import java.util.Scanner;
import java.util.Random;

/**
 * Project 2: Wordle.
 * 500.112 Gateway Computing: Java Spring 2023
 * Create a variation of the game WORDLE with words 4-6 letters
 * Melissa Martinez D4E3E5 mmart213 February 11, 2023
 */
 
public class Wordle {
   
   static final int MAX_GUESSES = 6;
   
   static final int MAX_HINTS = 2;

   public static void main(String[] args) {
      printIntro();
      
      //Initialize the game state.
      Random random = new Random();
      String word = newWord(random);
      String[] guesses = new String[MAX_GUESSES];
      for (int i = 0; i < guesses.length; i++) {
         guesses[i] = "";
      }
      char lastHint = '\0';
      int numGuesses = 0;
      int numHints = 0;
      Scanner scanner = new Scanner(System.in);
      boolean gameOver = false;

      //Run the game loop.
      while (!gameOver) {
         String command = printMenu(guesses, word, scanner);
         if ("h".equalsIgnoreCase(command)) {
            //Check whether the player has any hints left.
            if (numHints < MAX_HINTS) {
               lastHint = giveHint(word, lastHint, random);
               numHints++;
               printNumHintsRemaining(numHints);
            } else {
               System.out.println("Sorry, you're out of hints!");
            }
         } else if ("g".equalsIgnoreCase(command)) {
            printNumGuessesRemaining(numGuesses);
            String guess = getGuess(scanner);
            //Ensure the player's guess was valid and should count 
            //against the number of guesses taken.
            if (validateGuess(guess, word.length())) {
               String result = processGuess(word, guess);
               guesses[numGuesses++] = result;
               gameOver = checkGameOver(guess, word, numGuesses);
            }
         } else if ("e".equalsIgnoreCase(command)) {
            gameOver = true;
         } else {
            System.out.println("Invalid option! Try again!");
         }
      }
   }
   
   /**
   * Prints introduction.
   */
   public static void printIntro() {
      System.out.println("Welcome to Wordle! Menu options:");
      System.out.println("g/G: Make a guess");
      System.out.println("h/H: Get a hint");
      System.out.println("e/E: Exit");
   }
      
   /**
    * Prints the current game state and menu options, and prompts the
    * player for their choice.
    * 
    * @param guesses An array of the player's guesses.
    * @param word The correct word.
    * @param scanner a Scanner used to prompt the player for a menu choice.
    * @return The player's menu choice.
    */
   public static String printMenu(String[] guesses, String word,
                                  Scanner scanner) {
      //Iterate through all of the user's guess "slots" and print them.
      for (int i = 0; i < guesses.length; i++) {
         printGuess(guesses[i], word.length());
      }
      System.out.print("Enter a choice (G/H/E): ");
      return scanner.nextLine();
   }
   
   //Returns a guess
   static String getGuess(Scanner scanner) {
      System.out.print("Enter a guess: ");
      return scanner.nextLine();
   }

   /**
    * Gets random word (answer).
    * @param random Random generator for nums.
    * @return The new word of length 4-6.
    */
   public static String newWord(Random random) {
      return WordProvider.getWord(random.nextInt(3) + 4);
   }

   /**
    * Prints the guess.
    * @param guess The player's guess.
    * @param wordLength The length of the correct word.
    */
   public static void printGuess(String guess, int wordLength) {
      String out = "";
      if (guess.length() == 0) {
         for (int i = 0; i < wordLength; i++) {
            out += "_ ";
         }
      }
      else {
         for (int i = 0; i < wordLength; i++) {
            out += guess.substring(i, i + 1) + " ";
         }
      }
      out = out.substring(0, out.length() - 1);
      System.out.println(out);
   }
   
   /**
    * How many guesses remaining.
    * @param numGuesses Number of guesses used.
    */
   public static void printNumGuessesRemaining(int numGuesses) {
      if (numGuesses == 5) {
         System.out.println("You have 1 guess remaining.");
      }
      else {
         System.out.println("You have " + (6 - numGuesses) + 
            " guesses remaining.");
      }
   }

   /**
    * Prints number of hints remaining.
    * @param numHints Number of hints used.
    */
   public static void printNumHintsRemaining(int numHints) {
      if (numHints == 1) {
         System.out.println("You have 1 hint remaining.");
      }
      else {
         System.out.println("You have " + (2 - numHints) + " hints remaining.");
      }
   }

  /**
    * Gives new hint.
    * @param word Correct word.
    * @param lastHint Identity of last hint.
    * @param random Random generator.
    * @return Char for next hint.
    */
   public static char giveHint(String word, char lastHint, Random random) {
      int loc = random.nextInt(word.length());
      while (word.charAt(loc) == lastHint) {
         loc = random.nextInt(word.length());
      }
      System.out.println("Hint: the word contains the letter: " + 
         word.substring(loc, loc + 1) + ".");
      return word.charAt(loc);
   }

   /**
    * Checks the player's guess for validity(letters and length).
    * @param guess Player's guess.
    * @param correctLength The length of the correct word.
    * @return True if guess is valid, false otherwise
    */
   public static boolean validateGuess(String guess, int correctLength) {
      int counter = 0;
      for (int i = 0; i < guess.length(); i++) {
         if (!(Character.isLetter(guess.charAt(i)))) {
            counter++;
         }
      }
      if (counter == 0 && (guess.length()) == correctLength) {
         return true;
      }
      
      if (guess.length() != correctLength) {
         System.out.println("You must enter a guess of length " + 
            correctLength + ".");
      }
      
      if (counter > 0) {
         System.out.println("Your guess must only contain upper " +
            "case letters and lower case letters.");
      }
      return false;
   }

   /**
    * Checks all letters of guess and returns upper/lower case or ?
    * @param word correct word
    * @param guess player's guess
    * @return string with correct letters and/or ?.
    */
   public static String processGuess(String word, String guess) {
      String out = "";
      word = word.toUpperCase();
      guess = guess.toUpperCase();
      for (int i = 0; i < word.length(); i++) {
         if ((word.substring(i, i + 1)).equals(guess.substring(i, i + 1))) {
            out += (guess.substring(i, i + 1)).toUpperCase();
         }
         else if (word.indexOf(guess.substring(i, i + 1)) >= 0) {
            out += (guess.substring(i, i + 1)).toLowerCase();
         }
         else {
            out += "?";
         }
      }
      return out;
   }
   
   /**
    * Checks whether the game is over or not.
    * @param guess The player's guess.
    * @param word The correct word.
    * @param numGuesses How many guesses the player's made so far.
    * @return true if correct word or 6 guesses, false otherwise
    */
   public static boolean checkGameOver(String guess, String word, 
                                      int numGuesses) {
      guess = guess.toUpperCase();
      word = word.toUpperCase();
      if (guess.equals(word)) {
         System.out.println("Congrats, you guessed the word!");
         return true;
      }
      else if (numGuesses == 6) {
         System.out.println("Sorry, you ran out of guesses!");
         return true;
      }
      return false;
   }
}
