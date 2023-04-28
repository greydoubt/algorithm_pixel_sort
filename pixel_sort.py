from PIL import Image

# Load input image
input_file = 'input.jpg'
input_image = Image.open(input_file)

# Define parameters for pixel sorting
sort_rows = True # Sort rows instead of columns
start_row = 100 # Only sort rows starting from row 100
end_row = 200 # Only sort rows up to row 200

# Extract rows or columns to be sorted
if sort_rows:
    rows_to_sort = input_image.crop((0, start_row, input_image.width, end_row + 1))
    pixels_to_sort = list(rows_to_sort.getdata())
else:
    columns_to_sort = input_image.crop((start_row, 0, end_row + 1, input_image.height))
    pixels_to_sort = list(columns_to_sort.getdata())

# Sort pixels
sorted_pixels = sorted(pixels_to_sort)

# Create output image with sorted pixels
sorted_image = input_image.copy()
if sort_rows:
    sorted_rows = Image.new('RGB', (input_image.width, end_row - start_row + 1))
    sorted_rows.putdata(sorted_pixels)
    sorted_image.paste(sorted_rows, (0, start_row))
else:
    sorted_columns = Image.new('RGB', (end_row - start_row + 1, input_image.height))
    sorted_columns.putdata(sorted_pixels)
    sorted_image.paste(sorted_columns, (start_row, 0))

#Save sorted image

output_file = 'output.jpg'
sorted_image.save(output_file)