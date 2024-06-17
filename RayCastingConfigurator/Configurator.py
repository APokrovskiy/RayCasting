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
        # Настройки экрана
        self.title = 'My'  # Установка изначального заголовка
        Window.size = (800, 800)
        Clock.schedule_once(self.update_title, 0)  # Обновление заголовка через 0 секунд (после обновления экрана)

        background = FloatLayout()
        background.add_widget(Background())

        all_Widgets = BoxLayout(orientation='vertical')
        w_screen_resolution, a ,b  = self.__init_widgets_for_screen_resolution()
        w_position, a, b =  self.__init_widgets_for_position()
        
        w_fps, a = self.__init_widgets_for_fps()
        w_title, a = self.__input_widgets_for_title()
        w_rot_a, a = self.__init_widgets_for_rot_a()
        n_rays, a = self.__init_widgets_for_n_rays()
        w_vis_r, a = self.__init_widgets_for_vis_range()
        w_fov, a = self.__init_widgets_for_fov()
  
        
        
        all_Widgets.add_widget(w_screen_resolution)
        all_Widgets.add_widget(w_position)
        all_Widgets.add_widget(w_fps)
        all_Widgets.add_widget(w_title)
        all_Widgets.add_widget(w_rot_a)
        all_Widgets.add_widget(n_rays)
        all_Widgets.add_widget(w_vis_r)
        all_Widgets.add_widget(w_fov)
        all_Widgets.add_widget(self.__init_App_buttons())
        
        background.add_widget(all_Widgets)
       
        return background

    def __init_widgets_for_screen_resolution(self) -> Tuple[BoxLayout, TextInput, TextInput]:
        scrn_sz_layout = BoxLayout(orientation='horizontal')
        scrn_sz_layout.add_widget(Label(text = 'Screen size:', shorten = True))
        w_layout, w_inputs = self.__init_default_sett_box("Width:")
        scrn_sz_layout.add_widget(w_layout)
        h_layout, h_inputs = self.__init_default_sett_box("Height:")
        scrn_sz_layout.add_widget(h_layout)
        return scrn_sz_layout, w_inputs, h_inputs

    def __init_widgets_for_position(self) -> Tuple[BoxLayout, TextInput, TextInput]:
        position_layout = BoxLayout(orientation='horizontal')
        position_layout.add_widget(Label(text = 'Position:', shorten = True))
        x_layout, x_inputs = self.__init_default_sett_box("X:")
        position_layout.add_widget(x_layout)
        y_layout, y_inputs = self.__init_default_sett_box("Y:")
        position_layout.add_widget(y_layout)
        return position_layout, x_inputs, y_inputs
    
    def __init_widgets_for_fps(self) -> Tuple[BoxLayout, TextInput]:
        return self.__init_default_sett_box("Fps:")
    def __input_widgets_for_title(self) -> Tuple[BoxLayout, TextInput]:
        return self.__init_default_sett_box("Title:")
    def __init_widgets_for_rot_a(self)-> Tuple[BoxLayout, TextInput]:
        return self.__init_default_sett_box("Rotation Angle:")
    def __init_widgets_for_n_rays(self)-> Tuple[BoxLayout, TextInput]:
        return self.__init_default_sett_box("Rays:")
    def __init_widgets_for_vis_range(self)-> Tuple[BoxLayout, TextInput]:
        return self.__init_default_sett_box("Visual range:")
    def __init_widgets_for_fov(self)-> Tuple[BoxLayout, TextInput]:
        return self.__init_default_sett_box("Field Of View:")
    


    def __init_App_buttons(self) -> BoxLayout:
        buttons = BoxLayout(orientation='horizontal', size_hint_y=0.4)
        buttons.add_widget(Button(text = "Вернуть изначальные настройки", background_color = [1,1,1,0.4],background_normal=""))
        buttons.add_widget(Button(text = "Применить настройки", background_color = [1,1,1,0.4], background_normal=""))
        return buttons
    

    def __init_default_sett_box(self, title)-> Tuple[BoxLayout, TextInput]:
        layout = BoxLayout(orientation='horizontal')
        layout.add_widget(Label(text = title, shorten = True))
        inputs = TextInput(background_color = (1,1,1,0.1), foreground_color = (1,1,1,1))
        layout.add_widget(inputs)
        return layout, inputs

    def update_title(self, *args):
        Window.set_title('Configurator')  # Установка заголовка окна

if __name__ == '__main__':
    ConverterApp().run()

