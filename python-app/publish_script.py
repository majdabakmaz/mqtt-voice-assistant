import paho.mqtt.client as mqtt
import time

import tkinter as tk
from tkinter import simpledialog

from gtts import gTTS
from playsound import playsound

import pygame


# MQTT broker details
broker_address = "192.168.1.172"
broker_port = 1883
topic_for_publishing = "fromLyraT"
topics_for_subscribing = ["fromESP32","fromLyraT"]

tts = gTTS("I'm turning on the light", lang="en")   #save "on" sound
tts.save("turn_on.mp3")
tts = gTTS("I'm turning off the light", lang="en")  #save "off" sound
tts.save("turn_off.mp3")   

pygame.mixer.init()

def publish_message():
    user_input = entry.get()
    if user_input:
        client.publish(topic_for_publishing, user_input)
        entry.delete(0, tk.END)

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    for topic in topics_for_subscribing:
        client.subscribe(topic)

def on_message(client, userdata, msg):
    received_message = msg.payload.decode("utf-8")
    print("Recieved  (" +msg.topic+ ")  ~>  " + received_message)
    result_label.config(text="\nRecieved  (" +msg.topic+ ")  ~>  " + received_message)  #display message
    if "palim" in received_message:     #text to speech for turning lights
        pygame.mixer.music.load("turn_on.mp3")
        pygame.mixer.music.play()

    if "gasim" in received_message:
        pygame.mixer.music.load("turn_off.mp3")
        pygame.mixer.music.play()


client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect(broker_address, broker_port, 60)
client.loop_start()

root = tk.Tk()
root.title("MQTT")

entry = tk.Entry(root, font=("Helvetica", 12))
entry.pack(pady=20)

publish_button = tk.Button(root, text="Publish Message", command=publish_message)
publish_button.pack()

result_label = tk.Label(root, text="", font=("Helvetica", 14))
result_label.pack()

root.mainloop()

# Disconnect from the broker
client.disconnect()
