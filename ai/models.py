from django.db import models
from binary_forest_animal_classifier import *

# Create your models here.
class Binary_Tree_Model_v2(models.Model):
    input = models.TextField(blank=True)
    output = models.TextField(blank=True)
    created_at = models.DateTimeField(auto_now_add=True)

    def give_output(self):
        traits = self.input.split(',')
        return classify(traits)

    def save(self,*args,**kwargs):
        self.output = self.give_output()
        super().save(*args,**kwargs)




