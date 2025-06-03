const holdBtn = document.getElementById("hold");
const rollBtn = document.getElementById("roll");

holdBtn.addEventListener("click", hold);
rollBtn.addEventListener("click", roll);

let holdValue = 0;
let currPlayer = 1;
const holds = ["p1-hold", "p2-hold"];
const scoreNames = ["p1-score", "p2-score"];
const resultTexts = ["Player-1 turn!", "Player-2 turn!", "Player-1 won!", "Player-2 won!"];
let scores = [0, 0];

function hold() {
  scores[currPlayer - 1]+= holdValue;
  document.getElementById(scoreNames[currPlayer-1]).style.width = scores[currPlayer-1] + "%";
  document.getElementById(scoreNames[currPlayer-1]).setAttribute("aria-valuenow", scores[currPlayer-1]);
  document.getElementById(scoreNames[currPlayer-1]).innerText = scores[currPlayer-1];
  nextPlayer();
}


function roll() {
  const faceValue = Math.floor(Math.random() * 6) + 1;
  const output = "&#x268" + (faceValue - 1) + "; ";
  const die = document.getElementById("die");
  die.innerHTML = output;
  if(faceValue !== 1){
    holdValue += faceValue;
    updatePotential();
  } else if (faceValue === 1) {
    nextPlayer();
  }
}

function updatePotential(){
  document.getElementById(holds[currPlayer-1]).style.width = holdValue + "%";
  document.getElementById(holds[currPlayer-1]).setAttribute("aria-valuenow", holdValue);
  document.getElementById(holds[currPlayer-1]).innerText = holdValue;
  if((scores[currPlayer-1] + holdValue) >= 100){
    winner();
  }
}

function nextPlayer(){
  holdValue = 0;
  updatePotential();
  currPlayer = (currPlayer % 2) + 1;
  document.getElementById("result").innerText = resultTexts[currPlayer-1];
}

function winner(){
  holdBtn.removeEventListener("click", hold);
  rollBtn.removeEventListener("click", roll);
  holdBtn.setAttribute("class", "btn btn-danger disabled btn-lg w-100");
  rollBtn.setAttribute("class", "btn btn-success disabled btn-lg w-100");

  holdValue = 0;

  document.getElementById(holds[currPlayer-1]).style.width = holdValue + "%";
  document.getElementById(holds[currPlayer-1]).setAttribute("aria-valuenow", holdValue);
  document.getElementById(holds[currPlayer-1]).innerText = holdValue;
  
  document.getElementById(scoreNames[currPlayer-1]).setAttribute("aria-valuenow", 100);
  document.getElementById(scoreNames[currPlayer-1]).innerHTML = '100 &#127881';
  document.getElementById(scoreNames[currPlayer-1]).style.width = 100 + "%";
  document.getElementById(scoreNames[currPlayer-1]).setAttribute("class", "progress-bar bg-success");

  document.getElementById("result").innerText = resultTexts[currPlayer + 1];
}