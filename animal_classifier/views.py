from django.shortcuts import render, redirect
from ai.forms import Binary_Tree_Model_v2_form
from ai.models import Binary_Tree_Model_v2
from django.contrib import messages


def home(request):
    if request.method == 'POST':
        form = Binary_Tree_Model_v2_form(request.POST)
        if form.is_valid():
            form.save()
            obj = Binary_Tree_Model_v2.objects.latest('id')
            output = obj.give_output()
            form = Binary_Tree_Model_v2_form()
            return render(request,'home.html',{'output':output,'form': form})
    else:
        form = Binary_Tree_Model_v2_form()
    return render(request, 'home.html', {'form': form})




