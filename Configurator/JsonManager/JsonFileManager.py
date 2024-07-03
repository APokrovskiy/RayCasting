import json

from typing import Tuple
import os
import JsonManager.serialisation_classes as sclass

class JsonFileManager:
    def __init__(self, title:str) -> None:
        if(os.path.exists(title)):
            self.title = title
        else: raise FileExistsError(title + " not exists")

    def to_json(self, fps_limit, world_map, camera: sclass.Camera ):
        data = {"fps_limit": fps_limit,"world_map": world_map,"camera": camera.__dict__}
        with open(self.title, "w") as config:
            json.dump(data, config, indent=4)

    def from_json(self) -> Tuple[int, Tuple[str], sclass.Camera]:
        data = None
        with open(self.title, "r") as f:
            data = json.load(f)
        return data["fps_limit"], data["world_map"], sclass.Camera(dictionary=data["camera"])

