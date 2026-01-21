from django import forms
from .models import Binary_Tree_Model_v2

class Binary_Tree_Model_v2_form(forms.ModelForm):
    class Meta:
        model = Binary_Tree_Model_v2
        fields = ["input"]
        widgets = {
            "input": forms.Textarea(attrs={
                'placeholder': "Enter animal traits..."}),
        }