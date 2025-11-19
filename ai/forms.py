from django import forms
from .models import Binary_Tree_Model_v1

class Binary_Tree_Model_v1_form(forms.ModelForm):
    class Meta:
        model = Binary_Tree_Model_v1
        fields = ['x', 'y']