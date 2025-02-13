<script setup lang="ts">
import { AgGridVue } from "ag-grid-vue3";
import { colorSchemeDark, themeBalham } from 'ag-grid-community';

const bins = [
  { id: 1, w: 10, h: 20 },
  { id: 2, w: 20, h: 10 },
  { id: 3, w: 30, h: 30 },
  { id: 4, w: 40, h: 40 },
  { id: 5, w: 50, h: 50 },
  { id: 6, w: 60, h: 60 },
  { id: 7, w: 70, h: 70 },
  { id: 8, w: 80, h: 80 },
  { id: 9, w: 90, h: 90 },
  { id: 10, w: 100, h: 100 }
];

const items = [
  { w: 1, h: 10, x: 0, y: 0, binId: 1 },
  { w: 2, h: 20, x: 0, y: 0, binId: 2 },
  { w: 3, h: 30, x: 0, y: 0, binId: 3 },
  { w: 4, h: 40, x: 0, y: 0, binId: 4 },
  { w: 5, h: 50, x: 0, y: 0, binId: 5 },
  { w: 6, h: 60, x: 0, y: 0, binId: 6 },
  { w: 7, h: 70, x: 0, y: 0, binId: 7 },
  { w: 8, h: 80, x: 0, y: 0, binId: 8 },
  { w: 9, h: 90, x: 0, y: 0, binId: 9 },
  { w: 10, h: 100, x: 0, y: 0, binId: 10 },
  { w: 11, h: 110, x: 0, y: 0, binId: 1 },
  { w: 12, h: 120, x: 0, y: 0, binId: 2 },
  { w: 13, h: 130, x: 0, y: 0, binId: 3 },
  { w: 14, h: 140, x: 0, y: 0, binId: 4 },
  { w: 15, h: 150, x: 0, y: 0, binId: 5 },
  { w: 16, h: 160, x: 0, y: 0, binId: 6 },
  { w: 17, h: 170, x: 0, y: 0, binId: 7 },
  { w: 18, h: 180, x: 0, y: 0, binId: 8 },
  { w: 19, h: 190, x: 0, y: 0, binId: 9 },
  { w: 20, h: 200, x: 0, y: 0, binId: 10 }
]
</script>

<template>
  <BContainer fluid>
    <BRow>
      <BCol class="py-3 column d-flex flex-column" xl="3" lg="4" cols="6">
        <BCard header="Bins" class="mb-3 flex-grow-1" no-body>
          <AgGridVue
            style="height: 100%"
            :theme="themeBalham.withPart(colorSchemeDark)"
            :rowData="bins"
            :get-row-id="row => String(row.data.id)"
            :columnDefs="[
              { field: 'id', headerName: '#', editable: false },
              { field: 'w', headerName: 'Width', editable: true },
              { field: 'h', headerName: 'Height', editable: true }
            ]"
            @rowDataUpdated="(event: any) => event.api.autoSizeAllColumns()"
          />
        </BCard>
        <BCard header="Items" class="mb-3 flex-grow-1" no-body>
          <AgGridVue
            style="height: 100%"
            :theme="themeBalham.withPart(colorSchemeDark)"
            :rowData="items"
            :columnDefs="[
              { field: '#', valueGetter: 'node.rowIndex + 1', editable: false },
              { field: 'w', headerName: 'Width', editable: true },
              { field: 'h', headerName: 'Height', editable: true },
              { field: 'binId', headerName: 'Bin ID', editable: true },
              { field: 'x', headerName: 'X', editable: true },
              { field: 'y', headerName: 'Y', editable: true }
            ]"
            @rowDataUpdated="(event: any) => event.api.autoSizeAllColumns()"
          />
        </BCard>
        <BFormFloatingLabel label="Value type" class="mb-3">
          <BFormSelect :options="['Integer (all fractions will be rounded)', 'Float']" />
        </BFormFloatingLabel>
        <BFormFloatingLabel label="Algorithm" class="mb-3">
          <BFormSelect :options="['First Fit', 'Best Fit', 'Worst Fit']" />
        </BFormFloatingLabel>
        <BFormCheckbox switch class="mb-3">
          Show preview
        </BFormCheckbox>
        <BFormCheckbox switch class="mb-3">
          Show skyline
        </BFormCheckbox>
        <BFormCheckbox switch class="mb-3">
          Show free rectangles
        </BFormCheckbox>
        <BRow>
          <BCol>
            <BButton class="d-block w-100" variant="primary">Preview</BButton>
          </BCol>
          <BCol>
            <BButton class="d-block w-100" variant="primary">Evaluate</BButton>
          </BCol>
        </BRow>
      </BCol>
      <BCol class="column">column</BCol>
    </BRow>
  </BContainer>
</template>
<style lang="scss" scoped>
.column {
  height: 100vh;
  overflow-y: auto;
}
</style>