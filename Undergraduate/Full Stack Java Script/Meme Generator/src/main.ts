import "./style.css";

interface Meme {
    id: string;
    name: string;
    url: string;
    width: Number;
    height: Number;
    box_count: Number;
    captions: Number;
}

interface Memes {
    memes: Meme[];
}

interface MemeAPIResponse {
    success: boolean;
    data: Memes;
}

const memeAPI: string = "https://api.imgflip.com/get_memes";

const submitBtn = document.getElementById("submit") as HTMLButtonElement;
const topText = document.getElementById("input-top-text") as HTMLInputElement;
const botText = document.getElementById("input-bottom-text") as HTMLInputElement;
const errorSection = document.getElementById("error") as HTMLDivElement;
const memeSection = document.getElementById("meme") as HTMLElement;

let memeArray : Meme[];
let nextRender : Date;

const renderMemeAPI = async (): Promise<void> => {
    try{
        const response = await fetch(memeAPI);

        if(!response.ok) {
            throw new Error(`HTTP Error with status ${response.status}`);
        }

        const APIdata: MemeAPIResponse = await response.json();
        memeArray = Array.from(APIdata.data.memes);

        nextRender = new Date();
        nextRender.setDate(nextRender.getDate() + 1);

    } catch (error) {
        console.error("Error fetching data: ", error);
    }
}

const getMeme = async (): Promise< Meme | undefined > => {

    const currTime = new Date();

    if(currTime > nextRender){
        renderMemeAPI();
    }

    return memeArray[Math.floor(Math.random() * 99)];
}

const createMemeSection = (url : string, toptext: string, bottext: string):void => {
    formatMemeSection();

    const container = createContainer();

    const image = createImageObject(url);

    container.appendChild(image);

    container.appendChild(createTopText(toptext));

    container.appendChild(createBottomText(bottext));

    memeSection.appendChild(container);
}

const memeGeneration = async () => {

    errorSection.innerHTML = "";

    const meme: Meme | undefined = await getMeme();
    if (!meme){
        handleFetchingError();
        return;
    };

    const url : string = meme.url;
    
    createMemeSection(url, topText.value.trim(), botText.value.trim());
}

const handleFetchingError = () => {
    errorSection.innerHTML = "An error occurred while fetching memes!";
    createMemeSection("", "", "");
}

const handleTextError = () => {
    errorSection.innerHTML = "Please enter text in both input fields!";
    createMemeSection("", "", "");
}

const validateGo = () => {
    if(topText.value.trim() === "" || botText.value.trim() === ""){
        handleTextError();
    } else {
        memeGeneration();
    }
}

const handleTextKeyDown = (event: KeyboardEvent) => {
    if(event.key === "Enter") {
        if(topText.value.trim() === "" || botText.value.trim() === ""){
            handleTextError();
        } else {
            memeGeneration();
        }
    }
}

const createBottomText = (bottext: string) => {
    const bot = document.createElement("h2");
    bot.innerHTML = bottext;
    bot.classList.add("bottom-text");
    return bot;
}

const createTopText = (toptext: string)=> {
    const top = document.createElement("h2");
    top.innerHTML = toptext;
    top.classList.add("top-text");
    return top;
}

const createImageObject = (url: string) => {
    const image = document.createElement("img");
    image.src = url;
    image.classList.add("centered-image");
    return image;
}

const createContainer = () => {
    const container = document.createElement("div");
    container.classList.add("image-container");
    return container;
}

const formatMemeSection = () => {
    memeSection.innerHTML = "";
    memeSection.classList.add("meme-section", "w-[90%]", "mx-auto", "relative");
}

document.addEventListener("DOMContentLoaded", renderMemeAPI);
topText.addEventListener("keydown", handleTextKeyDown);
botText.addEventListener("keydown", handleTextKeyDown);
submitBtn.addEventListener("click", validateGo);