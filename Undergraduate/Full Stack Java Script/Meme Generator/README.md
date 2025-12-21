# Meme Generator

A simple web application that uses the [Imgflip API](https://imgflip.com/api) to randomly select one of the 100 most popular meme images used in the last 30 days on the Imgflip website. Additionally, the app allows a user to enter top and bottom texts to be overlay on the meme image.

## Features

- Randomly select a meme image from the 100 most popular memes.
- Overlay top and bottom text on the meme image.

## Run locally

- Clone this repository.
- Navigate to the project directory.
- Install dependencies using `pnpm install`.
- Start the development server with `pnpm run dev`.
- Open your browser and navigate to `http://localhost:5173`.
- Start generating memes!

I used this website to figure out images in HTML and how to center them: https://www.w3schools.com/howto/howto_css_image_center.asp
I used chatGpt to figure out that i should be doing event: KeyboardEvent instead of event: event for the keydown event
I used chatGpt to help me with the styling for the black background on the memes
I used this website to help with the black border on the text : https://www.geeksforgeeks.org/css-font-border/#using-textstroke-property