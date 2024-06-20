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
        Window.top = 100 # Это поможет разместить окно поверх других
        Window.left = 100 # Это поможет разместить окно поверх других
        Clock.schedule_once(self.update_title, 0)  # Обновление заголовка через 0 секунд (после обновления экрана)

        background = FloatLayout()
        background.add_widget(Background())

        all_Widgets = BoxLayout(orientation='vertical')

        menu = BoxLayout(orientation='horizontal')
        labels = self.__init_lables()
        inputs = self.__init_TextInputs()
        buttons = self.__init_App_buttons()
        menu.add_widget(labels)
        menu.add_widget(inputs)
        all_Widgets.add_widget(menu)
        all_Widgets.add_widget(buttons)
        background.add_widget(all_Widgets)
       
        return background

    def __init_lables(self) -> BoxLayout:
        labels = BoxLayout(orientation='vertical')
        labels.add_widget(Label(text = 'Screen Resolution:', shorten = True))
        labels.add_widget(Label(text='FPS:', shorten = True))
        labels.add_widget(Label(text='Title:', shorten = True))
        labels.add_widget(Label(text='Position:', shorten = True))
        labels.add_widget(Label(text='Rotation Angle:', shorten = True))
        labels.add_widget(Label(text='Rays:', shorten = True))
        labels.add_widget(Label(text='Visual Range:', shorten = True))
        labels.add_widget(Label(text='Field Of View:', shorten = True))
        return labels

    def __init_TextInputs(self) -> BoxLayout:
        textinputs = BoxLayout(orientation='vertical')
        textinputs.add_widget(TextInput(background_color = (1,1,1,0.1), foreground_color = (1,1,1,1)))
        textinputs.add_widget(TextInput(background_color = (1,1,1,0.1), foreground_color = (1,1,1,1)))
        textinputs.add_widget(TextInput(background_color = (1,1,1,0.1), foreground_color = (1,1,1,1)))
        textinputs.add_widget(TextInput(background_color = (1,1,1,0.1), foreground_color = (1,1,1,1)))
        textinputs.add_widget(TextInput(background_color = (1,1,1,0.1), foreground_color = (1,1,1,1)))
        textinputs.add_widget(TextInput(background_color = (1,1,1,0.1), foreground_color = (1,1,1,1)))
        textinputs.add_widget(TextInput(background_color = (1,1,1,0.1), foreground_color = (1,1,1,1)))
        textinputs.add_widget(TextInput(background_color = (1,1,1,0.1), foreground_color = (1,1,1,1)))
        return textinputs

    def __init_App_buttons(self) -> BoxLayout:
        buttons = BoxLayout(orientation='horizontal', size_hint_y=0.05)
        buttons.add_widget(Button(text = "Вернуть изначальные настройки", background_color = [1,1,1,0.4],background_normal=""))
        buttons.add_widget(Button(text = "Применить настройки", background_color = [1,1,1,0.4], background_normal=""))
        return buttons
    
    def update_title(self, *args):
        Window.set_title('Configurator')  # Установка заголовка окна

if __name__ == '__main__':
    ConverterApp().run()