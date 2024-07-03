from typing import Tuple

# Классы для сериализации настроек в json
class Camera:
    def __init__(self, position: tuple = None, speed: float = None, n_rays: int = None, 
                visual_range: int = None,  dictionary = None) -> None:
        if(dictionary):
            self.position = dictionary["position"]
            self.speed = dictionary["speed"]
            self.n_rays = dictionary["n_rays"]
            self.visual_range = dictionary["visual_range"]
        else:
            self.position = position
            self.speed = speed
            self.n_rays = n_rays
            self.visual_range = visual_range
        self.__is_valid()

    def __is_valid(self):
        if self.speed < 0: 
            raise ValueError("Camera.speed < 0")
        if self.n_rays <= 0: 
            raise ValueError("Camera.n_rays <= 0")
        if self.visual_range <= 0:
            raise ValueError("Camera.visual_range <= 0")

