import tkinter as tk
import fnmatch
import os
import pygame as mixer
import random

canvas = tk.Tk()
canvas.title("Music Player")
canvas.geometry("400x500")
canvas.config(bg='black')

rootpath = "C:\\Users\\Umanshiva\\Dropbox\\PC\\Desktop\\music"
pattern ="*.m4a"


def create_playlist(rootpath):
    music_files = [filename for filename in os.listdir(rootpath) if filename.endswith('.m4a')]
    random.shuffle(music_files)
    return music_files

playlist = create_playlist(rootpath)

def play_random_song(rootpath,playlist):
    mixer.init()
    random_song = random.choice(playlist)
    song_path = os.path.join(rootpath,random_song)
    mixer.music.load(song_path)
    mixer.music.play

listbox = tk.Listbox(canvas, fg = "cyan",bg = "black",width = 100,font = ('poppins',14)   )
listbox.pack(padx = 15,pady = 15)

label = tk.Label(canvas,text = '', bg = 'black', fg = 'yellow', font = ('poppins',10) )
label.pack(pady = 20)

playbutton = tk.Button(canvas, text='Play', command = lambda: play_random_song(rootpath,playlist))
playbutton.pack(pady = 20, side = 'left')

for root, dirs, files in os.walk(rootpath):
    for filename in fnmatch.filter(files, pattern):
       listbox.insert('end',filename)



canvas.mainloop()