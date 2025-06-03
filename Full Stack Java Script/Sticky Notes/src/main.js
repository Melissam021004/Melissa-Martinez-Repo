import "../style.css";

const newNote = document.getElementById("new-note");

const addNewNote = (notes, newNoteID, newText) => {
    return [...notes, {id: newNoteID, text: newText}];
}

const createStickyNotesApp = () => {
    let notes = [];
    let nextID = 1;
    let active = false;

    return {
        addNote: (newText) => {
            notes = addNewNote(notes, nextID, newText);
            nextID++;
        },
        removeNote: (idToRemove) => {
            notes = notes.splice(idToRemove, 1);
        },
        editNote: (event, notesItem) => {
            handleNoteKeydown(event, notesItem, notesItem.notesText, notesItem.notesTextArea);
        }
    }
}

let notes = [];
let nextID = 1;
let active = false;

const renderNotes = () => {
    const notesList = document.getElementById("notes-wall");
    notesList.innerHTML = "";

    for(let i = 0; i < notes.length; i++){
        const notesItem = createNotesItem(i);

        const trash = createTrashBtn(i);
        const notesText = createNotesText(i);
        const notesTextArea = createTextArea(i);

        notesItem.append(trash, notesText, notesTextArea)
        notesList.appendChild(notesItem);

        trash.addEventListener("click", handleTrash);
        notesItem.addEventListener("dblclick", () => handleNoteEditing(notesText, notesTextArea));
        notesTextArea.addEventListener("keydown", (event) => handleNoteKeydown(event, notesItem, notesText, notesTextArea));
    }
}

const createNotesText = (i) => {
    const notesText = document.createElement("div");
    notesText.classList.add("p-4", "note-text");
    notesText.innerHTML = notes[i].text;
    return notesText;
}

const createTextArea = (i) => {
    const notesTextArea = document.createElement("textarea");
    notesTextArea.classList.add("absolute", "top-0", "left-0", "hidden", "w-full", "h-full", "p-4", "transition-transform", "transform", "bg-yellow-300", "shadow-xl", "resize-none", "outline-rose-700", "outline-offset-0", "note-edit", "note", "hover:scale-105");
    notesTextArea.innerHTML = notes[i].text;
    return notesTextArea;
}

const createTrashBtn = (i) => {
    const trash = document.createElement("button");
    trash.id = i;
    trash.classList.add("absolute", "w-5", "h-5", "leading-5", "text-center", "transition-opacity", "opacity-0", "cursor-pointer", "delete-btn", "top-1", "right-1", "hover:opacity-100");
    trash.innerHTML = "🗑";
    return trash;
}

const createNotesItem = (i) => {
    const notesItem = document.createElement("div");
    notesItem.id = i;
    notesItem.classList.add("relative", "w-40", "h-40", "p-0", "m-2", "overflow-y-auto", "transition-transform", "transform", "bg-yellow-200", "shadow-lg", "note", "hover:scale-105");
    notesItem.style.whiteSpace = "pre-wrap"; //Ensures the white-space shows up properly
    return notesItem;
}

const handleNoteEditing = (notesText, notesTextArea) => {
    if(!active){ //Active is if a note is currently active, to prevent editing of multiple notes
        active = true;
        notesText.classList.add("hidden");
        notesTextArea.classList.remove("hidden");
        notesTextArea.focus(); //So it shows up as user types
    }
}

const handleNoteKeydown = (event, notesItem, notesText, notesTextArea) => {
    if (event.key === "Enter" && !event.shiftKey) {
        event.preventDefault(); //Prevents white space and instead finishes the editing
        handleNoteUpdate(notesItem, notesText, notesTextArea);
        active = false;
    }
}

const handleNoteUpdate = (notesItem, notesText, notesTextArea) => {
    //Updates the text across the whole note element
    notes[notesItem.id].text = notesTextArea.value;
    notesText.innerHTML = notes[notesItem.id].text;
    notesTextArea.classList.add("hidden");
    notesText.classList.remove("hidden");
}

const handleKeyDownNewNote = (event) => {    
    if (event.key === "Enter" && !event.shiftKey) {
        event.preventDefault(); //prevents new line
        if (event.target.value.trim() !== "") {
            notes.push({id: nextID++, text: event.target.value.trim()});
            event.target.value = "";
            renderNotes();
        }
    } else if (event.key === "Enter" && event.shiftKey) { //new line
        const pos = event.target.selectionStart;
        const before = event.target.value.substring(0, pos);
        const after = event.target.value.substring(pos);
        event.target.value = before + "\n" + after;
        event.target.selectionEnd = pos + 1;
        event.preventDefault();
    }
};

const handleTrash = (event) => {
    notes.splice(event.target.id, 1); //removes the note at that index
    renderNotes();
}

newNote.addEventListener("keydown", handleKeyDownNewNote);
document.addEventListener("DOMContentLoaded", renderNotes);