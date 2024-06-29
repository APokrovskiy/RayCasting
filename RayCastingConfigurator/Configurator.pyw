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
    jsonmanager.to_json(dsett.win, dsett.wrld, dsett.cmr)
    exit()

jsonmanager = JsonFileManager("settings.json")
window, world, camera = jsonmanager.from_json()


# Создание виджетов настройки одного параметра

def init_default_sett_box( title, text = "")-> Tuple[BoxLayout, TextInput]:
    layout = BoxLayout(orientation='horizontal', size_hint_y=None, height = 50)
    layout.add_widget(Label(text = title, shorten = True))
    inputs = TextInput(text=text, background_color = (1,1,1,0.1), foreground_color = (1,1,1,1))
    layout.add_widget(inputs)
    return layout, inputs

def init_widgets_for_screen_resolution() -> Tuple[BoxLayout, TextInput, TextInput]:
    scrn_sz_layout = BoxLayout(orientation='horizontal', size_hint_y=None, height =50)
    scrn_sz_layout.add_widget(Label(text = 'Screen size:', shorten = True))
    w_layout, w_inputs = init_default_sett_box("Width:", str(window.screen_size[0]))
    scrn_sz_layout.add_widget(w_layout)
    h_layout, h_inputs = init_default_sett_box("Height:",str(window.screen_size[1]))
    scrn_sz_layout.add_widget(h_layout)
    return scrn_sz_layout, w_inputs, h_inputs

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
w_screen_resolution, input_scrn_w ,input_scrn_h  = init_widgets_for_screen_resolution()
w_position, input_pos_x, input_pos_y =  init_widgets_for_position()
w_fps, input_fps = init_default_sett_box("Fps:", str(window.fps_limit))
w_title, input_title = init_default_sett_box("Title:", str(window.title))
w_rot_a, input_rot_a = init_default_sett_box("Rotation Angle:", str(camera.rotation_angle))
n_rays, input_rays = init_default_sett_box("Rays:", str(camera.n_rays))
w_vis_r, input_vis_r = init_default_sett_box("Visual range:",str(camera.visual_range))
w_fov, input_fov = init_default_sett_box("Field Of View:",str(camera.field_of_view))
btn_layout, btn, btn1 = init_app_buttons()

# CallBacks

def on_btn_click(instance): # TODO: Сделать отдельную функцию заполнения полей
    input_scrn_w.text = str(dsett.win.screen_size[0])
    input_scrn_h.text = str(dsett.win.screen_size[1])
    input_pos_x.text = str(dsett.cmr.position[0])
    input_pos_y.text = str(dsett.cmr.position[1])
    input_fps.text = str(dsett.win.fps_limit) 
    input_title.text = str(dsett.win.title)
    input_rot_a.text = str(dsett.cmr.rotation_angle)
    input_rays.text = str(dsett.cmr.n_rays)
    input_vis_r.text = str(dsett.cmr.visual_range)
    input_fov.text = str(dsett.cmr.field_of_view)

def on_btn1_click(instance):
    win = sclass.Window(input_title.text, (int(input_scrn_w.text), int(input_scrn_h.text)), int(input_fps.text))
    wrld = sclass.World(dsett.text_map, '1', 100)
    cmr = sclass.Camera((int(input_pos_x.text),int(input_pos_y.text)), 5, float(input_rot_a.text), int(input_rays.text), float(input_vis_r.text),  float(input_fov.text))
    try:
        local_jsonmanager = JsonFileManager("settings.json")
    except:
        with open("settings.json", "w") as file: pass 
        local_jsonmanager = JsonFileManager("settings.json")
    local_jsonmanager.to_json(win,wrld,cmr)

# Добавление  виджетов
content.add_widget(w_screen_resolution)
content.add_widget(w_position)
content.add_widget(w_fps)
content.add_widget(w_title)
content.add_widget(w_rot_a)
content.add_widget(n_rays)
content.add_widget(w_vis_r)
content.add_widget(w_fov)

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


