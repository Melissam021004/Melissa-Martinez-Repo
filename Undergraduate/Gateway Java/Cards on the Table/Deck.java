import java.util.Random;

/**
 * Project 5A
 * Deck class creates a deck with object cards that don't repeat.
 * Melissa Martinez D4E3E5 April 13, 2023
 */
public class Deck {
   
   Card[] allCards = new Card[52];
   Random rand = new Random();   
   
   /**
    * Creates a deck of 52 cards which are unique to one another.
    */
   public Deck() {
      int count = 0;
      for (int i = 1; i < 5; i++) {
         for (int j = 1; j < 14; j++) {
            allCards[count] = new Card(j, i);
            count++;
         }     
      }
   }
   
   /**
    * Converts the deck into a text format.
    * @return a string list of the deck
    */
   @Override
   public String toString() {
      String out = "";
      for (int i = 0; i < 52; i++) {
         out += allCards[i] + "\n";
      }
      
      return out;
   }
   
   /**
    * Shuffles the deck of cards in a random order.
    */
   public void shuffle() {
      Card[] copy = new Card[52];
      
      for (int i = 0; i < 52; i++) {
         copy[i] = allCards[i];
      }
      
      int k = 51;
      int j;
      
      for (int i = 0; i < 52; i++) {
         j = rand.nextInt(k + 1);
         allCards[i] = copy[j];
         copy[j] = copy[k];
         k--;
      }
   }
   
   /**
    * Sorts the shuffled deck by suit, then rank.
    */
   public void sort() {
      int pos = 0;
      Card temp;
      while (pos < 52) {
         if (pos == 0 || allCards[pos].compareTo(allCards[pos - 1]) >= 0) {
            pos++;
         }
         else {
            temp = allCards[pos];
            allCards[pos] = allCards[pos - 1];
            allCards[pos - 1] = temp;
            pos--;
         }
      }
   }
   
}