from machine import Pin, SoftI2C
import ssd1306
import gfx
from time import sleep

i2c = SoftI2C(scl=Pin(19), sda=Pin(18))

oled_width = 128
oled_height = 64
oled_zero = 0
oled = ssd1306.SSD1306_I2C(oled_width, oled_height, i2c)
graphics = gfx.GFX(oled_width, oled_height, oled.pixel)

def scale_data(data, new_min, new_max):
    current_min = min(data)
    current_max = max(data)
    current_range = current_max - current_min
    new_range = new_max-new_min
    scaled_data = [int(((d - current_min)/current_range)*new_range+new_min) for d in data]
    return scaled_data
    
def evenly_spaced_ints(data):
    step_size = oled_width / (len(data)-1)
    spaced_ints = [i * step_size for i in range(len(data))]
    spaced_ints = [round(x) for x in spaced_ints]
    return spaced_ints

def draw_lines(data):
    scaled_data = scale_data(data, oled_height, oled_zero)
    spaced_ints = evenly_spaced_ints(data)
    min_y_value = min(data)
    max_y_value = max(data)
    x1, x2 = spaced_ints[0], spaced_ints[1]
    y1, y2 = scaled_data[0], scaled_data[1]
    #oled.text(str(data[0]),x1,y1 if y1<55 else y1-10)
    for i in range(1, len(spaced_ints)):
        x2 = spaced_ints[i]
        y2 = scaled_data[i]
        graphics.line(x1,y1,x2,y2,1)
        #oled.text(str(data[i]),x2 if x2<96 else 96,y2 if y2<55 else y2-10)
        x1, y1 = x2, y2
    oled.text('Max: {}' .format(max_y_value),0,0)
    oled.text('Min: {}' .format(min_y_value),0,54)
    
def print_data(msg):
    
    my_string= msg.decode('utf-8')
    my_strings = my_string.split(' ')
    
    oled.fill(0)
    ii =  0
    for item in my_strings:
        oled.text(item,0,ii)
        ii = ii+10
    oled.show()

def plot_data(msg):
    my_string= msg.decode('utf-8')
    my_strings = my_string.split(' ')
    my_values = [float(item) for item in my_strings]
    
    scaled_y_values = scale_data(my_values, oled_height, oled_zero)
    x_values = (evenly_spaced_ints(scaled_y_values))
    
    print(scaled_y_values)
    print(x_values)
    
    oled.fill(0)
    
    draw_lines(my_values)

    oled.show()
    
