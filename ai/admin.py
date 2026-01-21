from django.contrib import admin
from .models import  Binary_Tree_Model_v2

# Register your models here.
@admin.register(Binary_Tree_Model_v2)
class Binary_Tree_Model_v2_admin(admin.ModelAdmin):
    list_display = ("id", "input", "output", "created_at")
    search_fields = ("output",)
    list_filter = ("output", "created_at")
    ordering = ("-created_at",)

    fields = ("input", "output")
    readonly_fields = ("output",)