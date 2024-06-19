from turtle import textinput
from kivy.app import App
from kivy.uix.label import Label
from kivy.core.window import Window
from kivy.clock import Clock
from kivy.uix.image import Image
from kivy.uix.widget import Widget
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.floatlayout import FloatLayout
from kivy.uix.textinput import TextInput
from kivy.uix.button import Button
from typing import Tuple
import default_settings as dsett
from JsonManager.JsonFileManager import RayCastingSettingsJsonFileManager
import JsonManager.serialisation_classes as sclass 

class Background(Widget):
    def __init__(self, **kwargs):
        super(Background, self).__init__(**kwargs)
        self.rect = Image(source='images/ConfiguratorBackground.png', allow_stretch=True, keep_ratio=False)
        self.add_widget(self.rect)

    def on_size(self, *args):
        self.rect.size = self.size
        self.rect.pos = self.pos



class ConverterApp(App):
    def build(self):
        try:
            self.jsonmanager = RayCastingSettingsJsonFileManager("settings.json")
            self.window, self.world, self.camera = self.jsonmanager.from_json()
        except(FileExistsError):
            self.window, self.world, self.camera = dsett.win, dsett.wrld, dsett.cmr
        

        # Настройки экрана
        self.title = 'My'  # Установка изначального заголовка
        Window.size = (800, 800)
        Clock.schedule_once(self.update_title, 0)  # Обновление заголовка через 0 секунд (после обновления экрана)

        background = FloatLayout()
        background.add_widget(Background())

        all_Widgets = BoxLayout(orientation='vertical')
        self.w_screen_resolution, self.input_scrn_w ,self.input_scrn_h  = self.__init_widgets_for_screen_resolution()
        self.w_position, self.input_pos_x, self.input_pos_y =  self.__init_widgets_for_position()
        
        self.w_fps, self.input_fps = self.__init_widgets_for_fps()
        self.w_title, self.input_title = self.__input_widgets_for_title()
        self.w_rot_a, self.input_rot_a = self.__init_widgets_for_rot_a()
        self.n_rays, self.input_rays = self.__init_widgets_for_n_rays()
        self.w_vis_r, self.input_vis_r = self.__init_widgets_for_vis_range()
        self.w_fov, self.input_fov = self.__init_widgets_for_fov()

        btn_layout, btn, btn1 = self.__init_App_buttons()
        
        btn.bind(on_press=self.on_btn_click)
        btn1.bind(on_press=self.on_btn1_click)
        all_Widgets.add_widget(self.w_screen_resolution)
        all_Widgets.add_widget(self.w_position)
        all_Widgets.add_widget(self.w_fps)
        all_Widgets.add_widget(self.w_title)
        all_Widgets.add_widget(self.w_rot_a)
        all_Widgets.add_widget(self.n_rays)
        all_Widgets.add_widget(self.w_vis_r)
        all_Widgets.add_widget(self.w_fov)
        all_Widgets.add_widget(btn_layout)
        
        background.add_widget(all_Widgets)
       
        return background

    def on_btn_click(self, instance): # TODO: Сделать отдельную функцию заполнения полей
        self.input_scrn_w.text = str(dsett.win.screen_size[0])
        self.input_scrn_h.text = str(dsett.win.screen_size[1])
        self.input_pos_x.text = str(dsett.cmr.position[0])
        self.input_pos_y.text = str(dsett.cmr.position[1])
        self.input_fps.text = str(dsett.win.fps_limit) 
        self.input_title.text = str(dsett.win.title)
        self.input_rot_a.text = str(dsett.cmr.rotation_angle)
        self.input_rays.text = str(dsett.cmr.n_rays)
        self.input_vis_r.text = str(dsett.cmr.visual_range)
        self.input_fov.text = str(dsett.cmr.field_of_view)

    def on_btn1_click(self, instance):
        win = sclass.Window(self.input_title.text, (int(self.input_scrn_w.text), int(self.input_scrn_h.text)), int(self.input_fps.text))
        wrld = sclass.World(dsett.text_map, '1', 100)
        cmr = sclass.Camera((int(self.input_pos_x.text),int(self.input_pos_y.text)), 5, float(self.input_rot_a.text), int(self.input_rays.text), float(self.input_vis_r.text),  float(self.input_fov.text))
        self.jsonmanager.to_json(win,wrld,cmr)

    def __init_widgets_for_screen_resolution(self) -> Tuple[BoxLayout, TextInput, TextInput]:
        scrn_sz_layout = BoxLayout(orientation='horizontal')
        scrn_sz_layout.add_widget(Label(text = 'Screen size:', shorten = True))
        w_layout, w_inputs = self.__init_default_sett_box("Width:", str(self.window.screen_size[0]))
        scrn_sz_layout.add_widget(w_layout)
        h_layout, h_inputs = self.__init_default_sett_box("Height:",str(self.window.screen_size[1]))
        scrn_sz_layout.add_widget(h_layout)
        return scrn_sz_layout, w_inputs, h_inputs

    def __init_widgets_for_position(self) -> Tuple[BoxLayout, TextInput, TextInput]:
        position_layout = BoxLayout(orientation='horizontal')
        position_layout.add_widget(Label(text = 'Position:', shorten = True))
        x_layout, x_inputs = self.__init_default_sett_box("X:", str(self.camera.position[0]))
        position_layout.add_widget(x_layout)
        y_layout, y_inputs = self.__init_default_sett_box("Y:", str(self.camera.position[0]))
        position_layout.add_widget(y_layout)
        return position_layout, x_inputs, y_inputs
    
    def __init_widgets_for_fps(self) -> Tuple[BoxLayout, TextInput]:
        return self.__init_default_sett_box("Fps:", str(self.window.fps_limit))
    def __input_widgets_for_title(self) -> Tuple[BoxLayout, TextInput]:
        return self.__init_default_sett_box("Title:", str(self.window.title))
    def __init_widgets_for_rot_a(self)-> Tuple[BoxLayout, TextInput]:
        return self.__init_default_sett_box("Rotation Angle:", str(self.camera.rotation_angle))
    def __init_widgets_for_n_rays(self)-> Tuple[BoxLayout, TextInput]:
        return self.__init_default_sett_box("Rays:", str(self.camera.n_rays))
    def __init_widgets_for_vis_range(self)-> Tuple[BoxLayout, TextInput]:
        return self.__init_default_sett_box("Visual range:",str(self.camera.visual_range))
    def __init_widgets_for_fov(self)-> Tuple[BoxLayout, TextInput]:
        return self.__init_default_sett_box("Field Of View:",str(self.camera.field_of_view))
    


    def __init_App_buttons(self) -> Tuple[BoxLayout, Button, Button]:
        buttons = BoxLayout(orientation='horizontal', size_hint_y=0.4)
        btn = Button(text = "Вернуть изначальные настройки", background_color = [1,1,1,0.4],background_normal="")
        btn1 = Button(text = "Применить настройки", background_color = [1,1,1,0.4], background_normal="")
        buttons.add_widget(btn)
        buttons.add_widget(btn1)
        return buttons, btn, btn1
    

    def __init_default_sett_box(self, title, text = "")-> Tuple[BoxLayout, TextInput]:
        layout = BoxLayout(orientation='horizontal')
        layout.add_widget(Label(text = title, shorten = True))
        inputs = TextInput(text=text, background_color = (1,1,1,0.1), foreground_color = (1,1,1,1))
        layout.add_widget(inputs)
        return layout, inputs

    def update_title(self, *args):
        Window.set_title('Configurator')  # Установка заголовка окна

if __name__ == '__main__':
    ConverterApp().run()

