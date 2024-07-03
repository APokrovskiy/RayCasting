# Импорты Фреймворка Kivy
from kivy.app import runTouchApp
from kivy.uix.label import Label
from kivy.core.window import Window
from kivy.clock import Clock
from kivy.uix.image import Image
from kivy.uix.widget import Widget
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.floatlayout import FloatLayout
from kivy.uix.textinput import TextInput
from kivy.uix.button import Button
from kivy.uix.scrollview import ScrollView

# Импорты стандартной библиотеки
from typing import Tuple
import os

# Импорты из пользовательских файлов
import default_settings as dsett
from JsonManager.JsonFileManager import JsonFileManager
import JsonManager.serialisation_classes as sclass 

if (not os.path.exists("settings.json")):
    with open("settings.json", "w") as file: pass 
    jsonmanager = JsonFileManager("settings.json")
    jsonmanager.to_json(dsett.fps_limit, dsett.text_map, dsett.cmr)
    exit()

jsonmanager = JsonFileManager("settings.json")
fps_limit , world_map, camera = jsonmanager.from_json()


# Создание виджетов настройки одного параметра

def init_default_sett_box( title, text = "")-> Tuple[BoxLayout, TextInput]:
    layout = BoxLayout(orientation='horizontal', size_hint_y=None, height = 50)
    layout.add_widget(Label(text = title, shorten = True))
    inputs = TextInput(text=text, background_color = (1,1,1,0.1), foreground_color = (1,1,1,1))
    layout.add_widget(inputs)
    return layout, inputs

def init_widgets_for_position() -> Tuple[BoxLayout, TextInput, TextInput]:
    position_layout = BoxLayout(orientation='horizontal', size_hint_y=None, height =50)
    position_layout.add_widget(Label(text = 'Position:', shorten = True))
    x_layout, x_inputs = init_default_sett_box("X:", str(camera.position[0]))
    position_layout.add_widget(x_layout)
    y_layout, y_inputs = init_default_sett_box("Y:", str(camera.position[0]))
    position_layout.add_widget(y_layout)
    return position_layout, x_inputs, y_inputs

def init_app_buttons() -> Tuple[BoxLayout, Button, Button]:
    buttons = BoxLayout(orientation='horizontal', size_hint_y=0.05)
    btn = Button(text = "Вернуть изначальные настройки", background_color = [1,1,1,0.4],background_normal="")
    btn1 = Button(text = "Применить настройки", background_color = [1,1,1,0.4], background_normal="")
    buttons.add_widget(btn)
    buttons.add_widget(btn1)
    return buttons, btn, btn1



# Функция Main

# Настройки экрана
Window.size = (800, 800)
Window.set_title('Ray-Casting Configurator')

# Создание основного Layout
configurator_app = FloatLayout()

# Загрузка фонового изображения
configurator_app.add_widget(Image(source='images/ConfiguratorBackground.png', allow_stretch=True, keep_ratio=False))

all_Widgets = BoxLayout(orientation='vertical')
content = BoxLayout(orientation='vertical', size_hint_y=None)
content.bind(minimum_height = content.setter('height'))

# Создание всех виджетов настроек

w_position, input_pos_x, input_pos_y =  init_widgets_for_position()
n_rays, input_rays = init_default_sett_box("Rays:", str(camera.n_rays))
w_fps_limit, input_fps = init_default_sett_box("FPS: ", str(fps_limit))
w_vis_r, input_vis_r = init_default_sett_box("Visual range:",str(camera.visual_range))
w_speed, input_speed = init_default_sett_box("Speed: ", str(camera.speed))
inputs_world = TextInput(text="\n".join(world_map), background_color = (1,1,1,0.1), foreground_color = (1,1,1,1), size_hint_y=None, multiline = True, readonly = False)
inputs_world.bind(minimum_height=inputs_world.setter('height'))
btn_layout, btn, btn1 = init_app_buttons()

# CallBacks

def on_btn_click(instance): # TODO: Сделать отдельную функцию заполнения полей
    input_pos_x.text = str(dsett.cmr.position[0])
    input_pos_y.text = str(dsett.cmr.position[1])
    input_rays.text = str(dsett.cmr.n_rays)
    input_vis_r.text = str(dsett.cmr.visual_range)
    input_speed.text = str(dsett.cmr.speed)
    inputs_world.text = '\n'.join(dsett.text_map)

def on_btn1_click(instance):
    string_map = inputs_world.text.split('\n')
    cmr = sclass.Camera((int(input_pos_x.text),int(input_pos_y.text)), float(input_speed.text), int(input_rays.text), float(input_vis_r.text))
    local_jsonmanager = JsonFileManager("settings.json")
    local_jsonmanager.to_json(int(input_fps.text),string_map, cmr)

# Добавление виджетов
content.add_widget(w_position)
content.add_widget(n_rays)
content.add_widget(w_vis_r)
content.add_widget(w_fps_limit)
content.add_widget(w_speed)
content.add_widget(Label(text = "World Map", shorten = True, size_hint_y=None, height = 50))
content.add_widget(inputs_world)

# Привязка callbacks к кнопкам
btn.bind(on_press=on_btn_click)
btn1.bind(on_press=on_btn1_click)

# Создание ScrollView и помещение виджетов из content
scrollview = ScrollView(bar_width=5,bar_color = [0.4,0.4,0.5,1])
scrollview.add_widget(content)


#Добавление всех виджетов
all_Widgets.add_widget(scrollview)
all_Widgets.add_widget(btn_layout)
configurator_app.add_widget(all_Widgets)

# Запуск программы
runTouchApp(configurator_app)


