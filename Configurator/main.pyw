from kivy.app import runTouchApp
from kivy.uix.label import Label
from kivy.core.window import Window
from kivy.uix.image import Image
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.floatlayout import FloatLayout
from kivy.uix.textinput import TextInput
from kivy.uix.button import Button
from kivy.uix.checkbox import CheckBox
from kivy.uix.scrollview import ScrollView

from typing import Tuple
import os

import dsetts
from Json_Manager import Json_Manager
import sclasses




# checking => CORRECT
def create_settings_box( title, text = "") -> Tuple[BoxLayout, TextInput]:

    box = BoxLayout(orientation='horizontal', size_hint_y=None, height = 50)
    box.add_widget(Label(text = title, shorten = True))

    text_input = TextInput(text=text, 
                            background_color = (1,1,1,0.1),
                            foreground_color = (1,1,1,1)
    )
    box.add_widget(text_input)

    return box, text_input


# checking => 
def create_position_settings_box( camera ) -> Tuple[BoxLayout, TextInput, TextInput]:
    box = BoxLayout(orientation='horizontal', size_hint_y=None, height =50)

    box.add_widget(Label(text = 'player position:', shorten = True))

    x_box, x_text_input = create_settings_box("x:", str(settings.camera.position[0]))
    box.add_widget(x_box)

    y_box, y_text_input = create_settings_box("y:", str(settings.camera.position[1]))
    box.add_widget(y_box)

    return box, x_text_input, y_text_input


def create_buttons() -> Tuple[BoxLayout, Button, Button]:
    box = BoxLayout(orientation='horizontal', size_hint_y=0.05)

    button1 = Button(text = "Return to default settings",
                    background_color = [1,1,1,0.4],
                    background_normal=""
    )
    button2 = Button(text = "Apply settings",
                    background_color = [1,1,1,0.4],
                    background_normal=""
    )

    box.add_widget(button1)
    box.add_widget(button2)

    return box, button1, button2


if __name__ == "__main__":

    if (not os.path.exists("settings.json")):
        with open("settings.json", "w") as file: pass 

        # Default Settings create
        jsonmanager = Json_Manager("settings.json")
        jsonmanager.to_json(dsetts.SETTINGS)

        exit(0)


    # Settings Import
    jsonmanager = Json_Manager("settings.json")
    settings = jsonmanager.from_json()


    Window.size = (500, 600)
    Window.set_title('Configurator')


    main_layout = FloatLayout()


    BACKGROUND = Image(source='images/ConfiguratorBackground.png', 
                    allow_stretch=True, 
                    keep_ratio=False
    )
    main_layout.add_widget(BACKGROUND)


    all_widgets = BoxLayout(orientation='vertical')

    settings_widgets = BoxLayout(orientation='vertical', size_hint_y=None)
    settings_widgets.bind(minimum_height = settings_widgets.setter('height'))


    position, x_text_input, y_text_input =  create_position_settings_box( settings.camera )

    n_rays, n_rays_text_input = create_settings_box("number of rays:", str(settings.camera.n_rays))
    fps, fps_text_input = create_settings_box("FPS: ", str(settings.fps))
    vis_range, vis_range_text_input = create_settings_box("visual range:",str(settings.camera.visual_range))
    speed, speed_text_input = create_settings_box("speed: ", str(settings.camera.speed))
    rot_speed, rot_speed_text_input = create_settings_box("rotation speed:", str(settings.camera.rot_speed))

    world_text_input = TextInput(text ='\n'.join(settings.world_map),
                                background_color = (1,1,1,0.1),
                                foreground_color = (1,1,1,1),
                                size_hint_y=None,
                                multiline = True,
                                readonly = False
    )

    # Authomatic Change world_text_input Size
    world_text_input.bind(minimum_height=world_text_input.setter('height'))

    button_layout, button1, button2 = create_buttons()


    def create_checkbox_settings(flag: bool, text: str) -> Tuple[BoxLayout, CheckBox]:
        box = BoxLayout(orientation='horizontal', size_hint_y=None, height = 50)

        checkbox = CheckBox()
        checkbox.active = flag
        def on_checkbox_active(checkbox, value):
            if value:
                flag = True
            else:
                flag = False
        checkbox.bind(active=on_checkbox_active)

        label = Label(text = text)

        box.add_widget(checkbox)
        box.add_widget(label)
        return box, checkbox


    minimap, minimap_checkbox = create_checkbox_settings(settings.widgets.minimap, "map visible")
    fps_visible, fps_checkbox = create_checkbox_settings(settings.widgets.fps, "fps visible")



    def on_button1_click(instance): 

        global settings
        settings = dsetts.SETTINGS

        x_text_input.text = str(dsetts.CAMERA.position[0])
        y_text_input.text = str(dsetts.CAMERA.position[1])
        n_rays_text_input.text = str(dsetts.CAMERA.n_rays)
        vis_range_text_input.text = str(dsetts.CAMERA.visual_range)
        speed_text_input.text = str(dsetts.CAMERA.speed)
        rot_speed_text_input.text = str(dsetts.CAMERA.rot_speed)

        world_text_input.text = '\n'.join(dsetts.TEXT_MAP)

        minimap_checkbox.active = dsetts.WIDGETS.minimap
        fps_checkbox.active = dsetts.WIDGETS.fps

        settings.widgets.minimap = dsetts.WIDGETS.minimap
        settings.widgets.fps = dsetts.WIDGETS.fps


    def on_button2_click(instance):

        string_map = world_text_input.text.split('\n')

        cmr = sclasses.Settings.Camera((int(x_text_input.text),
                            int(y_text_input.text)),
                            float(speed_text_input.text),
                            int(n_rays_text_input.text),
                            float(vis_range_text_input.text),
                            float(rot_speed_text_input.text)
        )

        widgets = sclasses.Settings.Visible_widgets(minimap_checkbox.active, fps_checkbox.active)

        global settings
        settings = sclasses.Settings(
            cmr,
            widgets, 
            int(fps_text_input.text), 
            string_map
        )

        jsonmanager = Json_Manager("settings.json")
        jsonmanager.to_json(settings)


    settings_widgets.add_widget(position)
    settings_widgets.add_widget(n_rays)
    settings_widgets.add_widget(vis_range)
    settings_widgets.add_widget(fps)
    settings_widgets.add_widget(speed)
    settings_widgets.add_widget(rot_speed)
    settings_widgets.add_widget(minimap)
    settings_widgets.add_widget(fps_visible)
    settings_widgets.add_widget(Label(text = "world map", shorten = True, size_hint_y=None, height = 50))
    settings_widgets.add_widget(world_text_input)


    button1.bind(on_press=on_button1_click)
    button2.bind(on_press=on_button2_click)


    scrollview = ScrollView(bar_width=5,bar_color = [0.4,0.4,0.5,1])
    scrollview.add_widget(settings_widgets)

    all_widgets.add_widget(scrollview)
    all_widgets.add_widget(button_layout)
    main_layout.add_widget(all_widgets)

    runTouchApp(main_layout)