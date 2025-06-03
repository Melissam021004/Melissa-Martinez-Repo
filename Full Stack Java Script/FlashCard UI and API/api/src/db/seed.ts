import { faker } from "@faker-js/faker";
import { db, connection } from "./index";
import { cards, decks } from "./schema";
import { sql } from "drizzle-orm";

async function seed() {
  console.log("Seeding the database...");

  // Clean the tables
  console.log("Cleaning existing data...");
  //await db.delete(cards);
  await db.delete(decks);
  await db.run(sql `DELETE FROM sqlite_sequence WHERE name IN ('posts', 'comments')`);

  const numDecks = 100;

  for(let i = 0; i < numDecks; i++){
    const title = faker.lorem.sentence({
      min: 1,
      max: 100
    });
    const numberOfCards = 10* Math.random();
    const deck = db.insert(decks).values({
      title,
      numberOfCards
    }).returning().get();

    const numCards = faker.number.int({min:1, max:10});
    for(let j = 0; j< numCards; j++){
      const front = faker.lorem.sentence({
        min: 1,
        max: 500
      });
      const back = faker.lorem.sentence({
        min: 1,
        max: 500
      });
      await db.insert(cards).values({
        front,
        back,
        deckId: deck.id
      })
    }
  }
}

seed()
  .catch((e) => {
    console.error("Seeding failed:");
    console.error(e);
  })
  .finally(() => {
    connection.close();
  });