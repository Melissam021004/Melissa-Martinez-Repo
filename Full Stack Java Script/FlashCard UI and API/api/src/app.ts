import { Hono } from "hono";
import { HTTPException } from "hono/http-exception";
import deckRoutes from "./routes/deck";
import cardRoutes from "./routes/card";

const app = new Hono();

app.get("/", (c) => {
  return c.text("Hello Hono!");
});

app.route("/", deckRoutes);
app.route("/", cardRoutes);

app.onError((err, c) => {
  console.error(`${err}`)

  if(err instanceof HTTPException){
    return err.getResponse(); //gets returned as a json to the client
  }
  return c.json({message : 'An unexpected error occurred.'}, 500);
})

export default app;
