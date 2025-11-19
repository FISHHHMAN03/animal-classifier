from django.db import models
from binary_tree import *
# Create your models here.
class Binary_Tree_Model_v1(models.Model):
    x = models.BooleanField(default=False)
    y = models.BooleanField(default=False)
    result = models.CharField(max_length=5)

    created_at = models.DateTimeField(auto_now_add=True,blank=True,null=True)

    def give_result(self):
        return predict(self.x,self.y)


    def save(self,*args,**kwargs):
        self.result = self.give_result()
        super().save(*args, **kwargs)

