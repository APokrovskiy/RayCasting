from typing import Tuple

class Settings:

    class Visible_widgets:
        def __init__(self, minimap: bool = None, fps: bool = None, dictionary = None):
            if(dictionary):
                self.minimap = dictionary["minimap"]
                self.fps = dictionary["fps"]
            else:
                self.fps = fps
                self.minimap = minimap

    class Camera:
        def __init__(self, position: tuple = None, speed: float = None, n_rays: int = None, 
                    visual_range: int = None, rot_speed: float = None, dictionary = None) -> None:
            if(dictionary):
                self.position = dictionary["position"]
                self.speed = dictionary["speed"]
                self.n_rays = dictionary["n_rays"]
                self.visual_range = dictionary["visual_range"]
                self.rot_speed = dictionary["rot_speed"]
            else:
                self.position = position
                self.speed = speed
                self.n_rays = n_rays
                self.rot_speed = rot_speed
                self.visual_range = visual_range
            self.__is_valid()

        def __is_valid(self):
            if self.speed < 0: 
                raise ValueError("Camera.speed < 0")
            if self.n_rays <= 0: 
                raise ValueError("Camera.n_rays <= 0")
            if self.visual_range <= 0:
                raise ValueError("Camera.visual_range <= 0")

    def __init__(self, cmr: Camera = None, widgets: Visible_widgets = None, fps: int = None, world_map: Tuple[str] = None, dictionary = None ):
        if (dictionary):
            self.camera = Settings.Camera(dictionary=dictionary["camera"])
            self.widgets = Settings.Visible_widgets(dictionary=dictionary["vis_widgets"])
            self.fps = dictionary["fps"]
            self.world_map = dictionary["world_map"]
        else:
            self.camera = cmr
            self.widgets = widgets
            self.fps = fps
            self.world_map = world_map
        self.__is_valid()

    def to_dict(self):
        return {"camera": self.camera.__dict__, "vis_widgets" : self.widgets.__dict__, 
                "fps": self.fps, "world_map": self.world_map}
    
    
    def __is_valid(self) -> bool:
        return True